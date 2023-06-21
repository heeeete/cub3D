/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 01:41:55 by huipark           #+#    #+#             */
/*   Updated: 2022/09/03 19:50:51 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	row_count(char const *s, char c)
{
	int	flag;
	int	cnt;

	cnt = 0;
	flag = 0;
	while (*s)
	{
		if (*s != c && flag == 0)
		{
			flag = 1;
			cnt++;
		}
		else if (*s == c)
			flag = 0;
		s++;
	}
	return (cnt);
}

static int	col_count(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i] != c && s[i])
	{
		cnt++;
		i++;
	}
	return (cnt);
}

static char	*col_malloc(char *res, char const *s, int cnt)
{
	int	i;

	i = 0;
	res = (char *)malloc(sizeof(char) * (cnt + 1));
	if (!res)
		return (0);
	while (cnt--)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

static void	ft_free(char **res, int row_cnt)
{
	int	i;

	i = 0;
	while (i < row_cnt)
	{
		free(res[i]);
		i++;
	}
	free(res);
}

char	**ft_split(char const *s, char c)
{
	int		row_cnt;
	int		i;
	char	**res;

	i = 0;
	row_cnt = row_count(s, c);
	res = (char **)malloc(sizeof (char *) * (row_cnt + 1));
	if (!res)
		return (0);
	while (i < row_cnt)
	{
		while (*s && *s == c)
			s++;
		res[i] = col_malloc(res[i], s, col_count(s, c));
		if (!res[i])
		{
			ft_free(res, i);
			return (0);
		}
		s += col_count(s, c);
		i++;
	}
	res[i] = 0;
	return (res);
}
