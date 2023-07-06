/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:26:48 by jimpark           #+#    #+#             */
/*   Updated: 2023/07/06 13:31:16 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	load_image(t_game *game, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->img = mlx_xpm_file_to_image(game->mlx, path, \
									&img->img_width, &img->img_height);
	if (!img->img)
		error("Error : textuer read error", NULL);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, \
									&img->size_l, &img->endian);
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = \
						img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(game->mlx, img->img);
}

static void	load_texture(t_game *game)
{
	t_img	img;

	load_image(game, game->map_info.texture[0], game->img.no, &img);
	load_image(game, game->map_info.texture[1], game->img.so, &img);
	load_image(game, game->map_info.texture[2], game->img.ea, &img);
	load_image(game, game->map_info.texture[3], game->img.we, &img);
}

void	init_texture(t_game *game)
{
	int	i;
	int	j;

	game->map_info.texture = (int **)wrap_malloc(sizeof(int *) * 4);
	i = 0;
	while (i < 4)
		game->map_info.texture[i++] = (int *)wrap_malloc \
											(sizeof(int) * (SIZE * SIZE));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < SIZE * SIZE)
			game->map_info.texture[i][j++] = 0;
		i++;
	}
	load_texture(game);
}
