/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:59:19 by jimpark           #+#    #+#             */
/*   Updated: 2023/06/26 20:16:09 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	rgb_range_check(t_rgb rgb)
{
	if (rgb.r < 0 || rgb.r > 255)
		error("RGB Error : Check the range of rgb", NULL);
	else if (rgb.g < 0 || rgb.g > 255)
		error("RGB Error : Check the range of rgb", NULL);
	else if (rgb.b < 0 || rgb.b > 255)
		error("RGB Error : Check the range of rgb", NULL);
}

static void	check_rgb(char *rgb_str)
{
	int	rgb_cnt;
	int	sep_cnt;

	if (!rgb_str)
		error("Error : invaild file", NULL);
	sep_cnt = 0;
	while (*rgb_str)
	{
		rgb_cnt = 0;
		while ((9 <= *rgb_str && *rgb_str <= 13) || (*rgb_str == 32))
			rgb_str++;
		while (ft_isdigit(*rgb_str) && rgb_cnt++ >= 0)
			rgb_str++;
		if ((rgb_cnt == 0) || ((*rgb_str != 0) && (*rgb_str != ',') && \
		(9 > *rgb_str || *rgb_str > 13) && (*rgb_str != 32)))
			error("RGB Error : rgb has to have only number", NULL);
		while ((9 <= *rgb_str && *rgb_str <= 13) || (*rgb_str == 32))
			rgb_str++;
		if ((*rgb_str != 0) && (*rgb_str != ','))
			error("RGB Error : there is space between number", NULL);
		else if ((*rgb_str != 0) && (*rgb_str++ == ','))
			sep_cnt++;
	}
	if (sep_cnt != 2)
		error("RGB Error : too many ','", NULL);
}

static void	set_rgb(t_rgb *rgb, char *rgb_str)
{
	char	**buf;
	int		i;

	buf = ft_split(rgb_str, ',');
	i = 0;
	while (i < 3)
	{
		if (!buf[i])
			error("RGB Error : There should be 3 numbers", NULL);
		if (i == 0)
			rgb->r = ft_atoi(buf[i]);
		else if (i == 1)
			rgb->g = ft_atoi(buf[i]);
		else if (i == 2)
			rgb->b = ft_atoi(buf[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		free (buf[i]);
		i++;
	}
	free (buf);
}

void	init_rgb(t_game *game)
{
	t_rgb	*f_rgb;
	t_rgb	*c_rgb;

	f_rgb = &(game->f_rgb);
	c_rgb = &(game->c_rgb);
	check_rgb(game->img.f);
	check_rgb(game->img.c);
	set_rgb(&game->f_rgb, game->img.f);
	set_rgb(&game->c_rgb, game->img.c);
	rgb_range_check(game->f_rgb);
	rgb_range_check(game->c_rgb);
	f_rgb->rgb = (f_rgb->r << 16 | f_rgb->g << 8 | f_rgb->b);
	c_rgb->rgb = (c_rgb->r << 16 | c_rgb->g << 8 | c_rgb->b);
}
