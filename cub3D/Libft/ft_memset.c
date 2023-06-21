/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 01:41:37 by huipark           #+#    #+#             */
/*   Updated: 2022/08/03 01:16:13 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*ptr, int value, size_t size)
{
	unsigned char	*temp;

	temp = ptr;
	while (size--)
	{
		*temp = (unsigned char)value;
		temp++;
	}
	return (ptr);
}
