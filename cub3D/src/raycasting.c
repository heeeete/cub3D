/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:52:57 by jimpark           #+#    #+#             */
/*   Updated: 2023/06/24 18:56:47 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>
#define HEIGHT 1080
#define WIDTH 1920

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

void	init_raycasting(t_ray *info, t_game *game)
{
	info->camera_x = 2 * info->x / (double)WIDTH - 1;
	info->dir_x = game->player.dir_x + game->player.planeX * info->camera_x;
	info->dir_y = game->player.dir_y + game->player.planeY * info->camera_x;
	info->map_x = (int)game->player.x;
	info->map_y = (int)game->player.y;
	info->delta_dist_x = fabs(1 / info->dir_x);
	info->delta_dist_y = fabs(1 / info->dir_y);
	info->hit = 0;
}

void calculateSideDistances(t_game *game, t_ray *info)
{
    if (info->dir_x < 0)
    {
        info->step_x = -1;
        info->side_dist_x = (game->player.x - info->map_x) * info->delta_dist_x;
    }
    else
    {
        info->step_x = 1;
        info->side_dist_x = (info->map_x + 1.0 - game->player.x) * info->delta_dist_x;
    }
    if (info->dir_y < 0)
    {
        info->step_y = -1;
        info->side_dist_y = (game->player.y - info->map_y) * info->delta_dist_y;
    }
    else
    {
        info->step_y = 1;
        info->side_dist_y = (info->map_y + 1.0 - game->player.y) * info->delta_dist_y;
    }
}

void findWallCollision(t_game* game, t_ray* info)
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
			info->perp_wall_dist = (info->map_x - game->player.x + (1 - info->step_x) / 2) / info->dir_x;
	else
			info->perp_wall_dist = (info->map_y - game->player.y + (1 - info->step_y) / 2) / info->dir_y;
}

void calculateDrawing(t_ray *info)
{
	info->line_height = (int)(HEIGHT / info->perp_wall_dist);
	info->draw_start = -info->line_height / 2 + HEIGHT / 2;
	if (info->draw_start < 0)
		info->draw_start = 0;
	info->draw_end = info->line_height / 2 + HEIGHT / 2;
	if (info->draw_end >= HEIGHT)
		info->draw_end = HEIGHT - 1;
	if (info->side == 0 && info->dir_x < 0)
		info->tex_num = 2; // West texture
	else if (info->side == 0 && info->dir_x > 0)
		info->tex_num = 3; // East texture
	else if (info->side == 1 && info->dir_y < 0)
		info->tex_num = 1; // South texture
	else if (info->side == 1 && info->dir_y > 0)
		info->tex_num = 0; // North texture
}

void calculate_wall_texture(t_game *game, t_ray *info)
{
	if (info->side == 0)
		info->wall_x = game->player.y + info->perp_wall_dist * info->dir_y;
	else
		info->wall_x = game->player.x + info->perp_wall_dist * info->dir_x;
	info->wall_x -= floor(info->wall_x);

	// x coordinate on the texture
	info->tex_x = (int)(info->wall_x * (double)SIZE);
	if (info->side == 0 && info->dir_y > 0)
		info->tex_x = SIZE - info->tex_x - 1;
	if (info->side == 1 && info->dir_y < 0)
		info->tex_x = SIZE - info->tex_x - 1;
}


static void	carc(t_game *game)
{
	t_ray	info;

	info.x = 0;
	if (game->map_info.re_buf == 1)
		set_buf_zero(game);
	paint_floor(game);
	while (info.x < WIDTH)
	{
		init_raycasting(&info, game);
		calculateSideDistances(game, &info);
		findWallCollision(game, &info);
		calculateDrawing(&info);
		calculate_wall_texture(game, &info);
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * SIZE / info.line_height;
		// Starting texture coordinate
		double texPos = (info.draw_start - HEIGHT / 2 + info.line_height / 2) * step;
		for (int y = info.draw_start; y < info.draw_end; y++)
		{
			// Cast the texture coordinate to integer, and mask with (SIZE - 1) in case of overflow
			int texY = (int)texPos & (SIZE - 1);
			texPos += step;
			int color = game->map_info.texture[info.tex_num][SIZE * texY + info.tex_x];
			// make color darker for y-sides: R, G, and B byte each divided through two with a "shift" and an "and"
			if (info.side == 1)
				color = (color >> 1) & 8355711;
			game->map_info.buf[y][info.x] = color;
			game->map_info.re_buf = 1;
		}
		info.x++;
	}
}

static void	draw(t_game *game)
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

int main_loop(t_game *game)
{
	carc(game);
	draw(game);
	return (0);
}
