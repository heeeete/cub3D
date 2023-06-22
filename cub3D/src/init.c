/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:10:14 by huipark           #+#    #+#             */
/*   Updated: 2023/06/23 02:10:19 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void nullify_struct_members(t_game *game)
{
	game->img.NO = NULL;
	game->img.SO = NULL;
	game->img.WE = NULL;
	game->img.EA = NULL;
	game->img.F = NULL;
	game->img.C = NULL;
}

void init_rgb(t_game *game)
{
	check_rgb(game->img.F);
	check_rgb(game->img.C);
	set_rgb(&game->f_rgb, game->img.F);
	set_rgb(&game->c_rgb, game->img.C);
	game->f_rgb.rgb = (game->f_rgb.r << 16 | game->f_rgb.g << 8 | game->f_rgb.b);
	game->c_rgb.rgb = (game->c_rgb.r << 16 | game->c_rgb.g << 8 | game->c_rgb.b);
}

void init(t_game *game, char *argv)
{
	int fd;

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
	search_map(game, &game->player);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1920, 1080, "cub3D");
	game->img.img = mlx_new_image(game->mlx, 1920, 1080);
	game->img.data = (int *)mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.size_l, &game->img.endian);
}
