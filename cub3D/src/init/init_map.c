/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:25:09 by jimpark           #+#    #+#             */
/*   Updated: 2023/06/26 15:23:40 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#define HEIGHT 1080
#define WIDTH 1920

static void	allocate_int_map(t_game *game)
{
	int		i;
	t_map	*map;

	map = &(game->map_info);
	map->int_map = wrap_malloc(sizeof(int *) * map->map_height);
	i = 0;
	while (i < map->map_height)
		map->int_map[i++] = wrap_malloc(sizeof(int) * map->max_width);
}

static int	check_map(char c)
{
	if (c == ' ' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	init_int_map(t_game *game)
{
	int	i;
	int	j;

	allocate_int_map(game);
	i = 0;
	while (i < game->map_info.map_height)
	{
		j = 0;
		while (j < game->map_info.max_width)
		{
			if (game->map_info.map[i][j] == '\0')
			{
				while (j < game->map_info.max_width)
					game->map_info.int_map[i][j++] = 0;
				break ;
			}
			else if (check_map(game->map_info.map[i][j]))
				game->map_info.int_map[i][j] = 0;
			else
				game->map_info.int_map[i][j] = game->map_info.map[i][j] - '0';
			j++;
		}
		i++;
	}
}

void	init_game_map(t_game *game)
{
	int	i;
	int	j;

	game->map_info.buf = (int **)malloc(sizeof(int *) * HEIGHT);
	i = 0;
	while (i < HEIGHT)
		game->map_info.buf[i++] = (int *)malloc(sizeof(int) * WIDTH);
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			game->map_info.buf[i][j++] = 0;
		i++;
	}
}
