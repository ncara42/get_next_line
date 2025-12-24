*Este proyecto ha sido creado como parte del currículo de 42 por ncaravac.*

# get_next_line

## Descripción
El objetivo de este proyecto es simple: programar una función que devuelva una línea leída de un file descriptor.

---

## Instrucciones

### Compilación
Para ejecutar el programa, usa 

```bash
gcc get_next_line.c get_next_line.h get_next_line_utils.c -o get_next.o
```

Luego ejecuta con


```bash
./get_next (archivo)
```

## Elección del algoritmo y estructura de datos

### Algoritmo

El algoritmo utilizado en `get_next_line` se basa en un recorrido sobre el buffer hasta identificar un salto de linea `\n`.
1. Mientras se busca, el programa guarda en la stash todo el contenido que va leyendo.
2. Una vez se encuentra, se guarda esta línea en una temporal y se actualiza la stash a partir del ultimo salto de línea.
3. Se imprime por salida la línea de turno.

---

### Estructura de datos

No se utilizan estructuras de datos complejas en este proyecto, ya que no son necesarias para cumplir los requisitos funcionales de `get_next_line`.  
Las herramientas principales utilizadas son:

- **Variables estáticas** (`static char *stash`) para no perder el valor de la variable incluso cuando la funcion termina.
- **Variables locales** para el control del índice y el conteo de caracteres impresos.
- **Funciones auxiliares** especializadas para , lo que mejora la legibilidad y modularidad del código.

---

## Recursos
1. Stackoverflow
2. Documentación de C
3. Inteligencia Artifical
<br> Manejo de errores, sugerencias de optimización y mejora de legibilidad del código.
