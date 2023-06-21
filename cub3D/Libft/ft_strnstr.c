/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 01:43:15 by huipark           #+#    #+#             */
/*   Updated: 2022/08/03 17:35:24 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*s;
	const char	*t;
	int			count;

	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack && len)
	{
		s = haystack;
		t = needle;
		count = 0;
		while (*s && *t && *s == *t && len)
		{
			s++;
			t++;
			len--;
			count++;
		}
		len += count;
		if (*t == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (0);
}
