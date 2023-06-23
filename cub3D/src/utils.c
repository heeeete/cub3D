/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:25:50 by jimpark           #+#    #+#             */
/*   Updated: 2023/06/23 18:55:56 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

#define RED "\033[0;31m"
#define RESET "\033[0m"

void	*wrap_malloc(size_t s)
{
	void	*ret;

	ret = malloc(s);
	if (ret == NULL)
		error ("MALLOC ERROR", NULL);
	return (ret);
}

void	error(char *msg, char *msg2)
{
	if (msg2)
		printf("\"%s\" %s\n", msg2, msg);
	else
		printf("%s%s%s\n", RED, msg, RESET);
	exit(1);
}

int	exit_game(void)
{
	exit(0);
}

int	check_format(char *str)
{
	int	n;

	if (!str)
		return (-1);
	n = ft_strlen(str);
	if (n < 5)
		return (-1);
	if (str[n - 4] != '.')
		return (-1);
	else if (str[n - 3] != 'c')
		return (-1);
	else if (str[n - 2] != 'u')
		return (-1);
	else if (str[n - 1] != 'b')
		return (-1);
	return (0);
}
