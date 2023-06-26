/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:52:39 by jimpark           #+#    #+#             */
/*   Updated: 2023/06/26 15:23:22 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	press_w(t_game *game)
{
	double	new_player_x;
	double	new_player_y;
	double	move_speed;

	move_speed = game->player.move_speed;
	new_player_x = game->player.x + game->player.dir_x * move_speed;
	new_player_y = game->player.y + game->player.dir_y * move_speed;
	if (game->map_info.int_map[(int)new_player_y][(int)game->player.x] == 0)
		game->player.y = new_player_y;
	if (game->map_info.int_map[(int)game->player.y][(int)new_player_x] == 0)
		game->player.x = new_player_x;
}

void	press_s(t_game *game)
{
	double	new_player_x;
	double	new_player_y;
	double	move_speed;

	move_speed = game->player.move_speed;
	new_player_x = game->player.x - game->player.dir_x * move_speed;
	new_player_y = game->player.y - game->player.dir_y * move_speed;
	if (game->map_info.int_map[(int)new_player_y][(int)game->player.x] == 0)
		game->player.y = new_player_y;
	if (game->map_info.int_map[(int)game->player.y][(int)new_player_x] == 0)
		game->player.x = new_player_x;
}

void	press_a(t_game *game)
{
	double	new_player_x;
	double	new_player_y;
	double	move_speed;

	move_speed = game->player.move_speed;
	new_player_x = game->player.x + game->player.dir_y * move_speed;
	new_player_y = game->player.y - game->player.dir_x * move_speed;
	if (game->map_info.int_map[(int)new_player_y][(int)game->player.x] == 0)
		game->player.y = new_player_y;
	if (game->map_info.int_map[(int)game->player.y][(int)new_player_x] == 0)
		game->player.x = new_player_x;
}

void	press_d(t_game *game)
{
	double	new_player_x;
	double	new_player_y;
	double	move_speed;

	move_speed = game->player.move_speed;
	new_player_x = game->player.x - game->player.dir_y * move_speed;
	new_player_y = game->player.y + game->player.dir_x * move_speed;
	if (game->map_info.int_map[(int)new_player_y][(int)game->player.x] == 0)
		game->player.y = new_player_y;
	if (game->map_info.int_map[(int)game->player.y][(int)new_player_x] == 0)
		game->player.x = new_player_x;
}

int	key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_W)
		press_w(game);
	else if (key == KEY_S)
		press_s(game);
	else if (key == KEY_A)
		press_a(game);
	else if (key == KEY_D)
		press_d(game);
	else if (key == KEY_LEFT_ARROW)
		press_left(&(game->player));
	else if (key == KEY_RIGHT_ARROW)
		press_right(&(game->player));
	mlx_clear_window(game->mlx, game->win);
	main_loop(game);
	return (0);
}
