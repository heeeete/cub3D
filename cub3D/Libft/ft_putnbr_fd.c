/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 01:41:46 by huipark           #+#    #+#             */
/*   Updated: 2022/08/05 15:15:19 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print(int n, int fd)
{
	if (n / 10 != 0)
	{
		print(n / 10, fd);
	}
	n = n % 10 + '0';
	write(fd, &n, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
			write(fd, "-2147483648", 11);
		else
		{
			write(fd, "-", 1);
			n *= -1;
			print(n, fd);
		}
	}
	else
		print(n, fd);
}
