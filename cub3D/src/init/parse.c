/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:04:40 by huipark           #+#    #+#             */
/*   Updated: 2023/06/25 14:23:27 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	nullify_struct_members(t_game *game)
{
	game->img.no = NULL;
	game->img.so = NULL;
	game->img.we = NULL;
	game->img.ea = NULL;
	game->img.f = NULL;
	game->img.c = NULL;
}

static void	check_texture_item(char *line, char *prefix, char **texture)
{
	if (!ft_strncmp(line, prefix, 3))
	{
		line += 3;
		while (*line == ' ')
			++line;
		*texture = ft_strdup(line);
		if (open(*texture, O_RDONLY) < 0)
			error("Error : texture error", prefix);
	}
}

void	check_texture(t_game *game, char *line)
{
	check_texture_item(line, "NO ", &(game->img.no));
	check_texture_item(line, "SO ", &(game->img.so));
	check_texture_item(line, "WE ", &(game->img.we));
	check_texture_item(line, "EA ", &(game->img.ea));
	if (!ft_strncmp(line, "F ", 2))
	{
		line += 2;
		while (*line == ' ')
			++line;
		game->img.f = ft_strdup(line);
	}
	if (!ft_strncmp(line, "C ", 2))
	{
		line += 2;
		while (*line == ' ')
			++line;
		game->img.c = ft_strdup(line);
	}
}

void	texture_parsing(t_game *game, char **map)
{
	int	i;

	i = 0;
	nullify_struct_members(game);
	while (i < 6)
		check_texture(game, map[i++]);
	if (!game->img.ea || !game->img.no || !game->img.we || !game->img.no)
		error("invaild file", NULL);
}

void	parse_map(t_game *game)
{
	char	**new_map;
	int		i;
	int		j;
	int		max_len;
	int		temp;

	i = 6;
	j = 0;
	new_map = wrap_malloc(sizeof(char *) * (game->map_info.map_height + 1));
	max_len = ft_strlen(game->map_info.map[i]);
	while (game->map_info.map[i])
	{
		new_map[j++] = ft_strdup(game->map_info.map[i++]);
		temp = ft_strlen(game->map_info.map[i]);
		if (max_len < temp)
			max_len = temp;
	}
	game->map_info.max_width = max_len;
	new_map[j] = NULL;
	i = 0;
	while (game->map_info.map[i])
		free(game->map_info.map[i++]);
	free(game->map_info.map);
	game->map_info.map = new_map;
}
