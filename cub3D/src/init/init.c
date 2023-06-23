/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:10:14 by huipark           #+#    #+#             */
/*   Updated: 2023/06/23 23:09:13 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	read_map(t_game *game, int fd)
{
	char	*line;
	char	*save;
	char	*temp_address;
	int		len;

	len = 0;
	line = get_next_line(fd);
	if (!line)
		error("EMPTY MAP", NULL);
	save = ft_strdup("");
	while (line)
	{
		temp_address = save;
		save = ft_strjoin(save, line);
		free(temp_address);
		free(line);
		line = get_next_line(fd);
	}
	game->map_info.map = ft_split(save, '\n');
	while (game->map_info.map[len])
		++len;
	game->map_info.map_height = len - 6;
	free(save);
}

void	search_map(t_game *game, t_player *player)
{
	int		i;
	int		j;
	int		prev_line_len;
	char	**map;

	i = -1;
	map = game->map_info.map;
	while (map[++i])
	{
		j = -1;
		if (i != 0)
			prev_line_len = ft_strlen(map[i - 1]);
		while (map[i][++j])
		{
			if (map[i][j] == '0')
			{
				if (check_invalid_map(i, j, prev_line_len, game))
					error("Error : map is invaild", NULL);
			}
			else if (check_map_error(map[i][j]))
				error("MAP Error", NULL);
			find_player_direction(player, map[i][j], i, j);
		}
	}
	check_player_position(game->map_info.map, player->x, player->y);
}

void	init(t_game *game, char *argv)
{
	int	fd;

	game->player.x = -1;
	game->player.y = -1;
	game->player.move_speed = 0.05;
	game->player.rot_speed = 0.05;
	game->map_info.re_buf = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		error("Error : file open error", NULL);
	read_map(game, fd);
	texture_parsing(game, game->map_info.map);
	init_rgb(game);
	free(game->img.F);
	free(game->img.C);
	game->img.F = NULL;
	game->img.C = NULL;
	parse_map(game);
	search_map(game, &game->player);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1920, 1080, "cub3D");
	game->img.img = mlx_new_image(game->mlx, 1920, 1080);
	game->img.data = (int *)mlx_get_data_addr(game->img.img, \
						&game->img.bpp, &game->img.size_l, &game->img.endian);
}
