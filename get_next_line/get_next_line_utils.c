/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaravac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 02:18:56 by ncaravac          #+#    #+#             */
/*   Updated: 2025/12/23 08:36:12 by ncaravac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;
	int		pos;

	i = 0;
	while (s1[i])
		i++;
	dup = (char *)malloc((i + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	pos = 0;
	while (s1[pos])
	{
		dup[pos] = s1[pos];
		pos++;
	}
	dup[pos] = '\0';
	return (dup);
}

char	*ft_strcat(char *str, const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	total_len;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = 0;
	while (s1[len1])
		len1++;
	len2 = 0;
	while (s2[len2])
		len2++;
	total_len = len1 + len2;
	str = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!str)
		return (NULL);
	ft_strcat(str, s1, s2);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	pos;
	unsigned int	s_len;
	unsigned int	max_len;

	if (!s)
		return (NULL);
	s_len = 0;
	while (s[s_len])
		s_len++;
	if (start >= s_len)
		return (ft_strdup(""));
	max_len = 0;
	while (s[start + max_len] && max_len < len)
		max_len++;
	sub = (char *)malloc(sizeof(char) * (max_len + 1));
	if (!sub)
		return (NULL);
	pos = 0;
	while (pos < max_len)
		sub[pos++] = s[start++];
	sub[pos] = '\0';
	return (sub);
}

char	*ft_strchr(const char *s, int c)
{
	int				pos;
	unsigned char	character;

	character = (unsigned char)c;
	pos = 0;
	while (s[pos])
	{
		if (s[pos] == character)
			return ((char *)&s[pos]);
		pos++;
	}
	if (s[pos] == character)
		return ((char *)&s[pos]);
	return (NULL);
}
