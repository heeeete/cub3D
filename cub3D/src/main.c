/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:18:36 by huipark           #+#    #+#             */
/*   Updated: 2023/06/23 02:20:17 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>
#define height 1080
#define width 1920

void	paint_floor(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < height / 2)
	{
		x = 0;
		while (x < width)
		{
			game->map_info.buf[y][x] = game->c_rgb.rgb;
			game->map_info.buf[height - y - 1][x] = game->f_rgb.rgb;
			x++;
		}
		y++;
	}
}

void carc(t_game *game)
{
	int x;

	x = 0;
	if (game->map_info.re_buf == 1)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				game->map_info.buf[i][j] = 0;
			}
		}
	}
	paint_floor(game);

	// WALL CASTING
	while (x < width)
	{
		double cameraX = 2 * x / (double)width - 1;
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
		int lineHeight = (int)(height / perpWallDist);

		// Calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + height / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + height / 2;
		if (drawEnd >= height)
			drawEnd = height - 1;

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
		double texPos = (drawStart - height / 2 + lineHeight / 2) * step;
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

void	draw(t_game *game)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			game->img.data[y * width + x] = game->map_info.buf[y][x];
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

int main_loop(t_game *game)
{
	carc(game);
	draw(game);
	return (0);
}

int key_press(int key, t_game *game)
{
	if (key == KEY_ESC){

		exit(0);
	}
   else if (key == KEY_W)
	{
		double new_player_x = game->player.x + game->player.dir_x * game->player.move_speed;
		double new_player_y = game->player.y + game->player.dir_y * game->player.move_speed;
		// if (game->map_info.int_map[(int)new_player_y][(int)new_player_x] == 0)
		// {
		// 	game->player.x = new_player_x;
		// 	game->player.y = new_player_y;
		// }
	 	if (game->map_info.int_map[(int)new_player_y][(int)game->player.x] == 0)
		{
			game->player.y = new_player_y;
		}
		if (game->map_info.int_map[(int)game->player.y][(int)new_player_x] == 0)
		{
			game->player.x = new_player_x;
		}
	}
	else if (key == KEY_S)
	{
		double new_player_x = game->player.x - game->player.dir_x * game->player.move_speed;
		double new_player_y = game->player.y - game->player.dir_y * game->player.move_speed;
		// if (game->map_info.int_map[(int)new_player_y][(int)new_player_x] == 0)
		// {
		// 	game->player.x = new_player_x;
		// 	game->player.y = new_player_y;
		// }
		if (game->map_info.int_map[(int)new_player_y][(int)game->player.x] == 0)
		{
			game->player.y = new_player_y;
		}
		if (game->map_info.int_map[(int)game->player.y][(int)new_player_x] == 0)
		{
			game->player.x = new_player_x;
		}
	}
	else if (key == KEY_A)
	{
		// Move left
		double new_player_x = game->player.x - game->player.dir_y * game->player.move_speed;
		double new_player_y = game->player.y + game->player.dir_x * game->player.move_speed;
		// if (game->map_info.int_map[(int)new_player_y][(int)new_player_x] == 0)
		// {
		// 	game->player.x = new_player_x;
		// 	game->player.y = new_player_y;
		// }
		if (game->map_info.int_map[(int)new_player_y][(int)game->player.x] == 0)
		{
			game->player.y = new_player_y;
		}
		if (game->map_info.int_map[(int)game->player.y][(int)new_player_x] == 0)
		{
			game->player.x = new_player_x;
		}
	}
	else if (key == KEY_D)
	{
		// Move right
		double new_player_x = game->player.x + game->player.dir_y * game->player.move_speed;
		double new_player_y = game->player.y - game->player.dir_x * game->player.move_speed;
		// if (game->map_info.int_map[(int)new_player_y][(int)new_player_x] == 0)
		// {
		// 	game->player.x = new_player_x;
		// 	game->player.y = new_player_y;
		// }
		if (game->map_info.int_map[(int)new_player_y][(int)game->player.x] == 0)
		{
			game->player.y = new_player_y;
		}
		if (game->map_info.int_map[(int)game->player.y][(int)new_player_x] == 0)
		{
			game->player.x = new_player_x;
		}
	}
	else if (key == KEY_LEFT_ARROW)
	{
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(game->player.rot_speed) - game->player.dir_y * sin(game->player.rot_speed);
		game->player.dir_y = oldDirX * sin(game->player.rot_speed) + game->player.dir_y * cos(game->player.rot_speed);
		double oldPlaneX = game->player.planeX;
		game->player.planeX = game->player.planeX * cos(game->player.rot_speed) - game->player.planeY * sin(game->player.rot_speed);
		game->player.planeY = oldPlaneX * sin(game->player.rot_speed) + game->player.planeY * cos(game->player.rot_speed);
	}
	else if (key == KEY_RIGHT_ARROW)
	{
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-game->player.rot_speed) - game->player.dir_y * sin(-game->player.rot_speed);
		game->player.dir_y = oldDirX * sin(-game->player.rot_speed) + game->player.dir_y * cos(-game->player.rot_speed);
		double oldPlaneX = game->player.planeX;
		game->player.planeX = game->player.planeX * cos(-game->player.rot_speed) - game->player.planeY * sin(-game->player.rot_speed);
		game->player.planeY = oldPlaneX * sin(-game->player.rot_speed) + game->player.planeY * cos(-game->player.rot_speed);
	}
	mlx_clear_window(game->mlx, game->win);
	main_loop(game);
	return (0);
}

void	load_image(t_game *game, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(game->mlx, img->img);
}

void load_texture(t_game *game)
{
	t_img   img;

	load_image(game, game->map_info.texture[0], game->img.NO, &img);
	load_image(game, game->map_info.texture[1], game->img.SO, &img);
	load_image(game, game->map_info.texture[2], game->img.WE, &img);
	load_image(game, game->map_info.texture[3], game->img.EA, &img);
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

int main(int argc, char *argv[])
{
	t_game game;

	if (argc != 2 || check_format(argv[1]) != 0)
		error("Error: <실행 파일> <맵 파일.cub>", NULL);
	game.map_info.buf = (int **)malloc(sizeof(int *) * height);
	for (int i = 0; i < height; i++)
	{
		game.map_info.buf[i] = (int *)malloc(sizeof(int) * width);
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			game.map_info.buf[i][j] = 0;
		}
	}


	init(&game, argv[1]);
	game.map_info.int_map = wrap_malloc(sizeof(int *) * game.map_info.map_height);
	for (int i = 0; i < game.map_info.map_height ; i++){
		game.map_info.int_map[i] = wrap_malloc(sizeof(int) * game.map_info.max_width);
	}
	for (int i = 0; i < game.map_info.map_height ; i++){
		for (int j = 0; j < game.map_info.max_width ; j++){
			if (game.map_info.map[i][j] == '\0')
			{
				for (int q = j ; q < game.map_info.max_width ; q++) {
					game.map_info.int_map[i][q] = 0;
				}
				break;
			}
			else if (game.map_info.map[i][j] == ' ')
				game.map_info.int_map[i][j] = 0;
			else if (game.map_info.map[i][j] == 'N' || game.map_info.map[i][j] == 'S' || game.map_info.map[i][j] == 'E' || game.map_info.map[i][j] == 'W')
				game.map_info.int_map[i][j] = 0;
			else
				game.map_info.int_map[i][j] = game.map_info.map[i][j] - '0';
		}
	}

	game.map_info.texture = (int **)wrap_malloc(sizeof(int *) * 4);
	for (int i = 0; i < 4; i++)
	{
		game.map_info.texture[i] = (int *)wrap_malloc(sizeof(int) * (SIZE * SIZE));
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < SIZE * SIZE; j++)
		{
			game.map_info.texture[i][j] = 0;
		}
	}

	load_texture(&game);
	////////////////////////////////////////////
	// printf("*****************파싱 결과*************\n\n");
	// int i = 0;
	// while (game.map_info.map[i])
	// {
	// 	int j = 0;
	// 	while (game.map_info.map[i][j])
	// 	{
	// 		printf("%c", game.map_info.map[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// 	printf("\n");
	// }
	// printf("FILE PATH : %s\n", game.img.NO);
	// printf("FILE PATH : %s\n", game.img.SO);
	// printf("FILE PATH : %s\n", game.img.EA);
	// printf("FILE PATH : %s\n", game.img.WE);
	// printf("F_RGB : %d\n", game.f_rgb.r);
	// printf("F_RGB : %d\n", game.f_rgb.g);
	// printf("F_RGB : %d\n", game.f_rgb.b);
	// printf("C_RGB : %d\n", game.c_rgb.r);
	// printf("C_RGB : %d\n", game.c_rgb.g);
	// printf("C_RGB : %d\n", game.c_rgb.b);
	// printf("PLAYER DIRECTION : %c\n\n", game.player.player_direction);
	// printf("*****************************************\n");
	////////////////////////////////////////////
;
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &exit_game, NULL);
	mlx_loop(game.mlx);
}
