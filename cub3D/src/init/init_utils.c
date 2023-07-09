/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:13:36 by huipark           #+#    #+#             */
/*   Updated: 2023/07/09 22:49:17 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_player_direction(t_player *player, char c)
{
	if (c == 'E' || c == 'W')
	{
		player->dir_x = 0.999999;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = 0.66;
		if (c == 'W')
		{
			player->dir_x = -player->dir_x;
			player->plane_y = -player->plane_y;
		}
	}
	else if (c == 'N' || c == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = -0.999999;
		player->plane_x = 0.66;
		player->plane_y = 0.0;
		if (c == 'S')
		{
			player->dir_y = -player->dir_y;
			player->plane_x = -player->plane_x;
		}
	}
}

void	find_player_direction(t_player *player, char c, int i, int j)
{
	if (c == 'W' || c == 'S' || c == 'N' || c == 'E')
	{
		if (player->x != -1 && player->y != -1)
			error("Error : There must be only one player", NULL);
		player->x = j + 0.5;
		player->y = i + 0.5;
		player->player_direction = c;
		init_player_direction(player, c);
	}
}

void	check_player_position(char **map, int x, int y)
{
	if (x == -1 && y == -1)
		error("Error : no players", NULL);
	else if (map[y + 1] == NULL || y - 1 == -1)
		error("Error : check player position", NULL);
	else if (map[y][x + 1] == '\0' || x - 1 == -1)
		error("Error : check player position", NULL);
	else if (map[y + 1][x] != '1' && map[y - 1][x] != '1' \
				&& map[y + 1][x] != '0' && map[y - 1][x] != '0')
		error("Error : check player position", NULL);
	else if (map[y][x + 1] != '1' && map[y][x - 1] != '1' \
				&& map[y][x + 1] != '0' && map[y][x - 1] != '0')
		error("Error : check player position", NULL);
}

int	check_invalid_map(int i, int j, int prev_line_len, t_game *game)
{
	char	**map;
	int		next_line_len;

	map = game->map_info.map;
	next_line_len = ft_strlen(map[i + 1]);
	if (j + 1 > prev_line_len || j + 1 > next_line_len)
		return (1);
	if (i == 0 || j == 0 || i == game->map_info.map_height \
		|| !map[i + 1]
		|| !map[i][j + 1] || map[i][j - 1] == ' ' || map[i][j + 1] == ' ' \
		|| map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
		return (1);
	return (0);
}

int	check_map_error(char c)
{
	if (c != '1' && c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != ' ')
		return (1);
	return (0);
}
