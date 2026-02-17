# get_next_line

*Proyecto desarrollado como parte del currículo de 42 por ncaravac.*

## Descripción

`get_next_line` es una función en C que lee y devuelve una línea desde un file descriptor. Este proyecto es fundamental para entender la gestión de memoria dinámica, el manejo de archivos y la lectura eficiente de datos en C.

La función lee línea por línea desde cualquier file descriptor (archivo, entrada estándar, etc.), independientemente del tamaño del buffer definido, manteniendo el estado entre llamadas mediante variables estáticas.

## Características

- ✅ Lee una línea completa desde un file descriptor
- ✅ Funciona con cualquier tamaño de BUFFER_SIZE
- ✅ Mantiene el estado entre llamadas sucesivas
- ✅ Gestión eficiente de memoria
- ✅ Devuelve NULL cuando llega al final del archivo o en caso de error
- ⚠️ Nota: La versión estándar soporta un file descriptor a la vez (variable estática única)

## Compilación y Uso

### Compilación

Para compilar el proyecto con un BUFFER_SIZE personalizado:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl_program
```

Si no se especifica BUFFER_SIZE, el valor por defecto es 512.

### Ejemplo de Uso

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("archivo.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```

## Funcionamiento Interno

### Algoritmo Principal

El algoritmo de `get_next_line` se divide en tres fases principales:

#### 1. **Lectura del Buffer** (`get_buffer`)
```
┌─────────────────────────────────────────┐
│  Lee BUFFER_SIZE bytes del fd           │
│  Almacena en stash acumulativa          │
│  Repite hasta encontrar '\n' o EOF      │
└─────────────────────────────────────────┘
```

- Lee bloques de BUFFER_SIZE bytes desde el file descriptor
- Concatena cada lectura al contenido acumulado en `stash`
- Se detiene cuando encuentra un salto de línea `\n` o cuando no hay más datos (EOF)
- Retorna el número de bytes leídos en la última operación

#### 2. **Extracción de Línea** (`get_line`)
```
┌─────────────────────────────────────────┐
│  Busca '\n' en stash                    │
│  Extrae línea hasta '\n' (incluido)     │
│  Actualiza stash con el resto           │
│  Si no hay '\n', devuelve todo          │
└─────────────────────────────────────────┘
```

- Busca el primer salto de línea en el contenido acumulado
- Extrae la línea completa (incluyendo el `\n`)
- Actualiza `stash` con el contenido restante después del `\n`
- Si no hay más `\n`, devuelve todo lo que queda y limpia `stash`

#### 3. **Gestión de Estado**
```
┌─────────────────────────────────────────┐
│  Variable estática: stash               │
│  Persiste entre llamadas                │
│  Mantiene datos no procesados           │
└─────────────────────────────────────────┘
```

### Flujo de Ejecución

```
┌──────────────────────┐
│   get_next_line(fd)  │
└──────────┬───────────┘
           │
           ├─→ ¿BUFFER_SIZE válido? ──No──→ return NULL
           │                  Sí
           ├─→ Reservar memoria para buffer
           │
           ├─→ get_buffer(&stash, buffer, fd)
           │        │
           │        ├─→ read(fd, buffer, BUFFER_SIZE)
           │        ├─→ Concatenar a stash
           │        └─→ ¿Encontró '\n'? ──Sí──→ break
           │                   No
           │                   └──→ Seguir leyendo
           │
           └─→ get_line(bytes, &stash, line)
                    │
                    ├─→ ¿Hay '\n' en stash?
                    │       │
                    │       ├─→ Sí: Extraer hasta '\n'
                    │       │    Actualizar stash con resto
                    │       │
                    │       └─→ No: Extraer todo
                    │            Liberar stash
                    │
                    └─→ return line
```

## Estructura del Proyecto

```
get_next_line/
├── get_next_line.h          # Header con prototipos y definiciones
├── get_next_line.c          # Implementación principal
├── get_next_line_utils.c    # Funciones auxiliares
└── README.md                # Este archivo
```

## Funciones Implementadas

### Función Principal

#### `char *get_next_line(int fd)`
Lee y devuelve la siguiente línea del file descriptor.

**Parámetros:**
- `fd`: File descriptor desde el cual leer

**Retorno:**
- La línea leída (incluyendo el `\n` si existe)
- `NULL` si no hay más líneas o en caso de error

### Funciones Auxiliares

#### `char *ft_strdup(const char *s1)`
Duplica una cadena de caracteres en memoria dinámica.

#### `char *ft_strjoin(char const *s1, char const *s2)`
Concatena dos cadenas en una nueva cadena.

#### `char *ft_substr(char const *s, unsigned int start, size_t len)`
Extrae una subcadena desde una posición dada.

#### `char *ft_strchr(const char *s, int c)`
Busca la primera ocurrencia de un carácter en una cadena.

#### `char *ft_strcat(char *str, const char *s1, const char *s2)`
Concatena dos cadenas en un buffer preasignado.

## Casos de Prueba Importantes

### 1. Archivo con múltiples líneas
```
línea 1\n
línea 2\n
línea 3
```
Debe leer cada línea correctamente, incluyendo la última sin `\n`.

### 2. Líneas muy largas
Una línea de 10,000 caracteres debe leerse correctamente independientemente del BUFFER_SIZE.

### 3. Archivo vacío
Debe retornar NULL inmediatamente.

### 4. BUFFER_SIZE = 1
Debe funcionar correctamente incluso con un buffer de 1 byte.

### 5. Múltiples file descriptors
```c
fd1 = open("file1.txt", O_RDONLY);
fd2 = open("file2.txt", O_RDONLY);
get_next_line(fd1);
get_next_line(fd2);
get_next_line(fd1);
```
Nota: La versión básica solo soporta un fd a la vez debido a la variable estática única.

## ⚙️ Variables y Parámetros

### BUFFER_SIZE
Define cuántos bytes se leen en cada llamada a `read()`. Puede definirse en tiempo de compilación:
```bash
gcc -D BUFFER_SIZE=1 ...
gcc -D BUFFER_SIZE=9999 ...
```

### Variable Estática: stash
Mantiene el contenido leído pero aún no devuelto entre llamadas sucesivas. Es crucial para el funcionamiento de la función ya que permite mantener el estado.

## Gestión de Memoria

El proyecto hace un uso intensivo de memoria dinámica:

1. **Asignación**: Cada línea devuelta es memoria dinámica que debe ser liberada por el llamador
2. **Liberación**: Las cadenas temporales se liberan internamente
3. **Pérdidas**: No debe haber memory leaks; todas las asignaciones deben tener su correspondiente `free()`

## ⚠️ Consideraciones Importantes

- ⚠️ El llamador es responsable de liberar la memoria devuelta por `get_next_line`
- ⚠️ No usar variables globales
- ⚠️ El comportamiento es indefinido si el file descriptor cambia entre llamadas
- ⚠️ BUFFER_SIZE debe ser mayor que 0
- ⚠️ La función debe funcionar correctamente tanto leyendo de archivos como de stdin