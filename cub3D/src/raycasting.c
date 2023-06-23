/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:52:57 by jimpark           #+#    #+#             */
/*   Updated: 2023/06/23 23:30:03 by jimpark          ###   ########.fr       */
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

static void	carc(t_game *game)
{
	int x;

	x = 0;
	if (game->map_info.re_buf == 1)
		set_buf_zero(game);
	paint_floor(game);

	// WALL CASTING
	while (x < WIDTH)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = game->player.dir_x + game->player.planeX * cameraX;
		double rayDirY = game->player.dir_y + game->player.planeY * cameraX;

		int mapX = (int)game->player.x;
		int mapY = (int)game->player.y;

		// length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		// length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		// what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; // was there a wall hit?
		int side;    // was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player.y) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// Check if ray has hit a wall
			if (game->map_info.int_map[mapY][mapX] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - game->player.x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - game->player.y + (1 - stepY) / 2) / rayDirY;

		// Calculate height of line to draw on screen
		int lineHeight = (int)(HEIGHT / perpWallDist);

		// Calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		// Calculate lowest and highest pixel to fill in current stripe


		// Texturing calculations
		int texNum;
		if (side == 0 && rayDirX < 0)
			texNum = 2; // West texture
		else if (side == 0 && rayDirX > 0)
			texNum = 3; // East texture
		else if (side == 1 && rayDirY < 0)
			texNum = 1; // South texture
		else if (side == 1 && rayDirY > 0)
			texNum = 0; // North texture

		// Calculate value of wallX
		double wallX;
		if (side == 0)
			wallX = game->player.y + perpWallDist * rayDirY;
		else
			wallX = game->player.x + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		// x coordinate on the texture
		int texX = (int)(wallX * (double)SIZE);
		if (side == 0 && rayDirX > 0)
			texX = SIZE - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = SIZE - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * SIZE / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (SIZE - 1) in case of overflow
			int texY = (int)texPos & (SIZE - 1);
			texPos += step;
			int color = game->map_info.texture[texNum][SIZE * texY + texX];
			// make color darker for y-sides: R, G, and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			game->map_info.buf[y][x] = color;
			game->map_info.re_buf = 1;
		}
		x++;
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
