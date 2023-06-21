/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 01:42:52 by huipark           #+#    #+#             */
/*   Updated: 2022/08/01 02:05:46 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len;

	len = ft_strlen(src);
	if (size != 0)
	{
		while (*src && size > 1)
		{
			*dest = *src;
			dest++;
			src++;
			size--;
		}
		*dest = '\0';
	}
	return (len);
}
