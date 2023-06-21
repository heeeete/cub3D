/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:56:37 by huipark           #+#    #+#             */
/*   Updated: 2022/08/01 01:49:29 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*temp1;
	unsigned char	*temp2;

	temp1 = (unsigned char *)s1;
	temp2 = (unsigned char *)s2;
	while (n--)
	{
		if (*temp1 > *temp2)
			return (*temp1 - *temp2);
		else if (*temp1 < *temp2)
			return (*temp1 - *temp2);
		temp1++;
		temp2++;
	}
	return (0);
}
