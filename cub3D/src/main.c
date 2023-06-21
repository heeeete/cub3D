/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:18:36 by huipark           #+#    #+#             */
/*   Updated: 2023/06/21 16:47:16 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>
#define height 1080
#define width 1920

int absolute_value(int x) {
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}


void draw_rectangle(t_game *game, int x, int y, int color)
{
    int i;
    int j;

    y *= SIZE;
    x *= SIZE;
    i = 0;
    while (i < SIZE)
    {
        j = 0;
        while (j < SIZE)
        {
            int pixel_index = (y + i) * (game->map_info.max_width * SIZE) + (x + j);
            if (game->map_info.map[y / SIZE][x / SIZE] == 'N')
            {
                if (i == SIZE / 2 && j == SIZE / 2)
                    game->img.data[pixel_index] = 0xFF0000; // 빨간색 점
                else
                    game->img.data[pixel_index] = 0xFFFFFF; // 흰색
            }
            else
            {
                game->img.data[pixel_index] = color;
            }
            j++;
        }
        i++;
    }
}

void draw_rectangles(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map_info.map_height)
    {
        j = 0;
        while (game->map_info.map[i][j])
        {
            int color;
            if (game->map_info.map[i][j] == '1')
                color = 0x000000; // 벽의 색상
            else
                color = 0xFFFFFF; // 빈 공간의 색상
            draw_rectangle(game, j, i, color);
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void draw_rectangles2(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map_info.map_height)
    {
        j = 0;
        while (game->map_info.map[i][j])
        {
            int color;
            if (game->map_info.map[i][j] == '1')
                color = 0x00FF000; // 벽의 색상
            else
                color = 0xFFFFFF; // 빈 공간의 색상
            draw_rectangle(game, j, i, color);
            j++;
        }
        i++;
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
        game->map_info.re_buf = 0;
    }
    while (x < width)
    {
        double cameraX = 2 * x / (double)width - 1;
        double rayDirX = game->player.dir_x + game->player.planeX * cameraX;
        double rayDirY = game->player.dir_y + game->player.planeY * cameraX;

        int mapX = (int)game->player.x;
        int mapY = (int)game->player.y;

        // Length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        // Length of ray from one x or y-side to next x or y-side
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        // What direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; // Was there a wall hit?
        int side; // Was a NS or a EW wall hit?

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
            // Jump to next map square, OR in x-direction, OR in y-direction
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

        // Calculate distance projected on camera direction
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

        // Texturing calculations
        char texNum = game->map_info.int_map[mapY][mapX];

        // Calculate value of wallX
        double wallX;
        if (side == 0)
            wallX = game->player.y + perpWallDist * rayDirY;
        else
            wallX = game->player.x + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        // X coordinate on the texture
        int texX = (int)(wallX * (double)SIZE);
        if (side == 0 && rayDirX > 0)
            texX = SIZE - texX - 1;
        if (side == 1 && rayDirY < 0)
            texX = SIZE - texX - 1;

        // Calculate step and initial texture position
        double step = 1.0 * SIZE / lineHeight;
        double texPos = (drawStart - height / 2 + lineHeight / 2) * step;

        for (int y = drawStart; y < drawEnd; y++)
        {
            // Cast the texture coordinate to integer and mask with (SIZE - 1) in case of overflow
            int texY = (int)texPos & (SIZE - 1);
            texPos += step;

            // Get the texture color for the current pixel
            int color = game->map_info.texture[texNum][SIZE * texY + texX];

            // Make color darker for y-sides: R, G, and B byte each divided through two with a "shift" and an "and"
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
	if (key == KEY_ESC)
		exit(0);
   else if (key == KEY_W)
	{
		double new_player_x = game->player.x + game->player.dir_x * game->player.move_speed;
		double new_player_y = game->player.y + game->player.dir_y * game->player.move_speed;
		if (game->map_info.int_map[(int)new_player_y][(int)new_player_x] == 0)
		{
			game->player.x = new_player_x;
			game->player.y = new_player_y;
		}
	}
    else if (key == KEY_S)
	{
		double new_player_x = game->player.x - game->player.dir_x * game->player.move_speed;
		double new_player_y = game->player.y - game->player.dir_y * game->player.move_speed;
		if (game->map_info.int_map[(int)new_player_y][(int)new_player_x] == 0)
		{
			game->player.x = new_player_x;
			game->player.y = new_player_y;
		}
	}
    else if (key == KEY_A)
	{
		// Move left
		double new_player_x = game->player.x - game->player.dir_y * game->player.move_speed;
		double new_player_y = game->player.y + game->player.dir_x * game->player.move_speed;
		if (game->map_info.int_map[(int)new_player_y][(int)new_player_x] == 0)
		{
			game->player.x = new_player_x;
			game->player.y = new_player_y;
		}
	}
	else if (key == KEY_D)
	{
		// Move right
		double new_player_x = game->player.x + game->player.dir_y * game->player.move_speed;
		double new_player_y = game->player.y - game->player.dir_x * game->player.move_speed;
		if (game->map_info.int_map[(int)new_player_y][(int)new_player_x] == 0)
		{
			game->player.x = new_player_x;
			game->player.y = new_player_y;
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

int main(int argc, char *argv[])
{
	t_game game;

    game.player.dir_x = -1.0;
    game.player.dir_y = 0.0;
    game.player.planeX = 0.0;
    game.player.planeY = 0.66;
    game.player.move_speed = 0.05;
    game.player.rot_speed = 0.05;
    game.map_info.re_buf = 0;
	if (argc != 2)
		exit(1);

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
            else if (game.map_info.map[i][j] == 'N')
                game.map_info.int_map[i][j] = 0;
            else
                game.map_info.int_map[i][j] = game.map_info.map[i][j] - '0';
        }
    }

    for (int i = 0; i < game.map_info.map_height ; i++){
        for (int j = 0; j < game.map_info.max_width ; j++){
            printf("%d", game.map_info.int_map[i][j]);
        }
        printf("\n");
    }

    game.map_info.texture = (int **)wrap_malloc(sizeof(int *) * game.map_info.map_height);
    for (int i = 0; i < game.map_info.map_height; i++)
	{
		game.map_info.texture[i] = (int *)wrap_malloc(sizeof(int) * (SIZE * SIZE));
	}
    for (int i = 0; i < game.map_info.map_height; i++)
	{
		for (int j = 0; j < SIZE * SIZE; j++)
		{
			game.map_info.texture[i][j] = 0;
		}
	}

    for (int x = 0; x < SIZE; x++)
	{
		for (int y = 0; y < SIZE; y++)
		{
			int xorcolor = (x * 256 / SIZE) ^ (y * 256 / SIZE);
			int ycolor = y * 256 / SIZE;
			int xycolor = y * 128 / SIZE + x * 128 / SIZE;
			game.map_info.texture[0][SIZE * y + x] = 65536 * 254 * (x != y && x != SIZE - y); //flat red texture with black cross
			game.map_info.texture[1][SIZE * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			game.map_info.texture[2][SIZE * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			game.map_info.texture[3][SIZE * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			game.map_info.texture[4][SIZE * y + x] = 256 * xorcolor; //xor green
			game.map_info.texture[5][SIZE * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			game.map_info.texture[6][SIZE * y + x] = 65536 * ycolor; //red gradient
			game.map_info.texture[7][SIZE * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	}

    printf("%f   %f  adsasd\n", game.player.x, game.player.y);
	////////////////////////////////////////////
	printf("*****************파싱 결과*************\n\n");
	int i = 0;
	while (game.map_info.map[i])
	{
		int j = 0;
		while (game.map_info.map[i][j])
		{
			printf("%c", game.map_info.map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
	printf("FILE PATH : %s\n", game.img.NO);
	printf("FILE PATH : %s\n", game.img.SO);
	printf("FILE PATH : %s\n", game.img.EA);
	printf("FILE PATH : %s\n", game.img.WE);
	printf("F_RGB : %d\n", game.f_rgb.r);
	printf("F_RGB : %d\n", game.f_rgb.g);
	printf("F_RGB : %d\n", game.f_rgb.b);
	printf("C_RGB : %d\n", game.c_rgb.r);
	printf("C_RGB : %d\n", game.c_rgb.g);
	printf("C_RGB : %d\n", game.c_rgb.b);
	printf("PLAYER DIRECTION : %c\n\n", game.player.player_direction);
	printf("*****************************************\n");
	////////////////////////////////////////////
	// draw_rectangles(&game);
    main_loop(&game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &exit_game, NULL);
	// mlx_loop_hook(game.mlx ,&main_loop, &game);
	// mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
	mlx_loop(game.mlx);
	// system("leaks cub3D");

}
