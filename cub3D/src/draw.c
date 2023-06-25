/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:55:00 by huipark           #+#    #+#             */
/*   Updated: 2023/06/25 14:18:22 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_raycasting(t_ray *info, t_game *game)
{
	info->camera_x = 2 * info->x / (double)WIDTH - 1;
	info->dir_x = game->player.dir_x + game->player.plane_x * info->camera_x;
	info->dir_y = game->player.dir_y + game->player.plane_y * info->camera_x;
	info->map_x = (int)game->player.x;
	info->map_y = (int)game->player.y;
	info->delta_dist_x = fabs(1 / info->dir_x);
	info->delta_dist_y = fabs(1 / info->dir_y);
	info->hit = 0;
}

static void	paint_floor(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			game->map_info.buf[y][x] = game->c_rgb.rgb;
			game->map_info.buf[HEIGHT - y - 1][x] = game->f_rgb.rgb;
			x++;
		}
		y++;
	}
}

static void	set_buf_zero(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			game->map_info.buf[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	carc(t_game *game)
{
	t_ray	info;

	info.x = 0;
	if (game->map_info.re_buf == 1)
		set_buf_zero(game);
	paint_floor(game);
	while (info.x < WIDTH)
	{
		init_raycasting(&info, game);
		calculate_side_distances(game, &info);
		fine_wall_collision(game, &info);
		calculate_drawing(&info);
		calculate_wall_texture(game, &info);
		draw_texture(game, &info);
		info.x++;
	}
}

void	draw(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			game->img.data[y * WIDTH + x] = game->map_info.buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
