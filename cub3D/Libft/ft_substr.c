/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 01:43:45 by huipark           #+#    #+#             */
/*   Updated: 2022/08/10 20:00:14 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	connect(char const *s, char *res, unsigned int start, size_t len)
{
	size_t			j;

	j = 0;
	while (s[start] && j < len)
	{
		res[j++] = s[start++];
	}
	return (j);
}

static size_t	len_check(size_t len, unsigned int start, char const *s)
{
	size_t	s_len;

	s += start;
	s_len = ft_strlen(s);
	if (s_len < len)
		return (s_len);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;

	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	len = len_check(len, start, s);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res[connect(s, res, start, len)] = 0;
	return (res);
}
