/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:46:40 by huipark           #+#    #+#             */
/*   Updated: 2022/08/03 16:15:38 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned char		*dst;
	const unsigned char	*sc;

	dst = dest;
	sc = src;
	if (dst == sc)
		return (dest);
	else if (dst < sc)
	{
		while (size--)
			*dst++ = *sc++;
	}
	else
	{
		dst += size;
		sc += size;
		while (size--)
			*--dst = *(unsigned char *)--sc;
	}
	return (dest);
}
