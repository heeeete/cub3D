/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:52:57 by jimpark           #+#    #+#             */
/*   Updated: 2023/06/25 14:22:53 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calculate_side_distances(t_game *game, t_ray *info)
{
	if (info->dir_x < 0)
	{
		info->step_x = -1;
		info->side_dist_x = (game->player.x - info->map_x) * info->delta_dist_x;
	}
	else
	{
		info->step_x = 1;
		info->side_dist_x = (info->map_x + 1.0 - game->player.x) \
		* info->delta_dist_x;
	}
	if (info->dir_y < 0)
	{
		info->step_y = -1;
		info->side_dist_y = (game->player.y - info->map_y) * info->delta_dist_y;
	}
	else
	{
		info->step_y = 1;
		info->side_dist_y = (info->map_y + 1.0 - game->player.y) \
		* info->delta_dist_y;
	}
}

void	fine_wall_collision(t_game *game, t_ray *info)
{
	while (info->hit == 0)
	{
		if (info->side_dist_x < info->side_dist_y)
		{
			info->side_dist_x += info->delta_dist_x;
			info->map_x += info->step_x;
			info->side = 0;
		}
		else
		{
			info->side_dist_y += info->delta_dist_y;
			info->map_y += info->step_y;
			info->side = 1;
		}
		if (game->map_info.int_map[info->map_y][info->map_x] > 0)
			info->hit = 1;
	}
	if (info->side == 0)
		info->perp_wall_dist = (info->map_x - game->player.x + \
		(1 - info->step_x) / 2) / info->dir_x;
	else
		info->perp_wall_dist = (info->map_y - game->player.y + \
		(1 - info->step_y) / 2) / info->dir_y;
}

void	calculate_drawing(t_ray *info)
{
	info->line_height = (int)(HEIGHT / info->perp_wall_dist);
	info->draw_start = -info->line_height / 2 + HEIGHT / 2;
	if (info->draw_start < 0)
		info->draw_start = 0;
	info->draw_end = info->line_height / 2 + HEIGHT / 2;
	if (info->draw_end >= HEIGHT)
		info->draw_end = HEIGHT - 1;
	if (info->side == 0 && info->dir_x < 0)
		info->tex_num = 2;
	else if (info->side == 0 && info->dir_x > 0)
		info->tex_num = 3;
	else if (info->side == 1 && info->dir_y < 0)
		info->tex_num = 1;
	else if (info->side == 1 && info->dir_y > 0)
		info->tex_num = 0;
}

void	calculate_wall_texture(t_game *game, t_ray *info)
{
	if (info->side == 0)
		info->wall_x = game->player.y + info->perp_wall_dist * info->dir_y;
	else
		info->wall_x = game->player.x + info->perp_wall_dist * info->dir_x;
	info->wall_x -= floor(info->wall_x);
	info->tex_x = (int)(info->wall_x * (double)SIZE);
	if ((info->side == 0 && info->dir_x > 0) || \
	(info->side == 1 && info->dir_y < 0))
		info->tex_x = SIZE - info->tex_x - 1;
}

void	draw_texture(t_game *game, t_ray *info)
{
	int	y;
	int	color;

	y = info->draw_start;
	info->step = 1.0 * SIZE / info->line_height;
	info->tex_pos = (info->draw_start - HEIGHT / 2 + info->line_height / 2) \
	* info->step;
	while (y < info->draw_end)
	{
		info->tex_y = (int)info->tex_pos & (SIZE - 1);
		info->tex_pos += info->step;
		color = game->map_info.texture[info->tex_num] \
		[SIZE * info->tex_y + info->tex_x];
		if (info->side == 1)
			color = (color >> 1) & 8355711;
		game->map_info.buf[y][info->x] = color;
		game->map_info.re_buf = 1;
		y++;
	}
}
