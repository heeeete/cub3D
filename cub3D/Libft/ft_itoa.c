/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 01:40:58 by huipark           #+#    #+#             */
/*   Updated: 2022/08/05 15:14:47 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strsize(int n)
{
	int	cnt;

	cnt = 0;
	if (n <= 0)
		cnt++;
	while (n != 0)
	{
		cnt++;
		n = n / 10;
	}
	return (cnt);
}

static char	*init_vallue(char *res, int n, int flag)
{
	if (flag == 1)
	{
		n *= -1;
		res += 1;
		flag = 0;
	}
	if (n != 0)
	{
		init_vallue(res + 1, n / 10, flag);
	}
	*res = n % 10 + '0';
	return (res);
}

static void	swap(char *res, int size, int flag, int j)
{
	int		i;
	char	temp;

	i = 0;
	if (flag == 1)
		i = 1;
	size /= 2;
	while (size--)
	{
		temp = res[i];
		res[i] = res[j];
		res[j] = temp;
		i++;
		j--;
	}
}

char	*ft_itoa(int n)
{
	int		size;
	int		flag;
	char	*res;
	int		j;

	flag = 0;
	size = strsize(n);
	res = (char *)malloc(sizeof(char) * size + 1);
	if (!res)
		return (0);
	j = size - 1;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_strlcpy(res, "-2147483648", 12);
			return (res);
		}
		flag = 1;
		res[0] = '-';
	}
	init_vallue(res, n, flag);
	swap(res, size, flag, j);
	res[size] = 0;
	return (res);
}
