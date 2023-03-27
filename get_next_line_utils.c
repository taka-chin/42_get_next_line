/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:32:49 by tyamauch          #+#    #+#             */
/*   Updated: 2023/03/23 22:39:18 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		str++;
		len++;
	}
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	char	*result;

	result = (char *)s;
	while (*result)
	{
		if (*result == (char)c)
		{
			return (result);
		}
		result++;
	}
	if (c == '\0')
	{
		return (result);
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	length;
	size_t	i;

	i = 0;
	length = ft_strlen(s1) + 1;
	str = malloc(length);
	if (!str)
	{
		return (NULL);
	}
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*tmp;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc(s1_len + s2_len + 1);
	if (!str)
		return (NULL);
	tmp = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	str = tmp;
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_length;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	s_length = ft_strlen(s);
	if (start >= s_length || len == 0)
		return (ft_strdup(""));
	else if (len > s_length - start)
		len = s_length - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (s[start + i] && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
