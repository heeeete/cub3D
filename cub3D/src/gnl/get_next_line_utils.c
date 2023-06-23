/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:26:59 by jimpark           #+#    #+#             */
/*   Updated: 2023/06/23 23:12:56 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	if (!str)
		return (0);
	count = 0;
	while (*str)
	{
		str++;
		count++;
	}
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (!c && *s == '\0')
		return ((char *)s);
	return (0);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t			dest_len;
	size_t			src_len;
	unsigned int	i;

	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	while (src[i] && dest_len + i + 1 < size)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	if (size > dest_len)
		return (dest_len + src_len);
	return (src_len + size);
}

char	*ft_strdup(const char *s1)
{
	int			i;
	const int	len = ft_strlen(s1);
	char		*dest;

	i = 0;
	dest = (char *)wrap_malloc(sizeof(char) * (len + 1));
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(const char *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*dest;

	if (!s1)
		return (ft_strdup(s2));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!dest)
		return (0);
	ft_strlcpy(dest, s1, s1_len + 1);
	ft_strlcat(dest, s2, s1_len + s2_len + 1);
	return (dest);
}
