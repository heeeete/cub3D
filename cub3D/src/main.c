/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:18:36 by huipark           #+#    #+#             */
/*   Updated: 2023/06/25 14:18:42 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main_loop(t_game *game)
{
	carc(game);
	draw(game);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2 || check_format(argv[1]) != 0)
		error("Error: <실행 파일> <맵 파일.cub>", NULL);
	init_game_map(&game);
	init(&game, argv[1]);
	init_int_map(&game);
	init_texture(&game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &exit_game, NULL);
	mlx_loop(game.mlx);
}
