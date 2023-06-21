/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:04:40 by huipark           #+#    #+#             */
/*   Updated: 2023/06/16 18:05:58 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void check_texture_item(char *line, char *prefix, char **texture) {
    if (!ft_strncmp(line, prefix, 3)) {
        line += 3;
        while (*line == ' ')
            ++line;
        *texture = ft_strdup(line);
        if (open(*texture, O_RDONLY) < 0)
            error("Error : texture error", prefix);
    }
}

void check_texture(t_game *game, char *line)
{
	check_texture_item(line, "NO ", &(game->img.NO));
    check_texture_item(line, "SO ", &(game->img.SO));
    check_texture_item(line, "WE ", &(game->img.WE));
    check_texture_item(line, "EA ", &(game->img.EA));
	if (!ft_strncmp(line, "F ", 2)) {
		line += 2;
		while (*line == ' ')
			++line;
		game->img.F = ft_strdup(line);
	}
	if (!ft_strncmp(line, "C ", 2)) {
		line += 2;
		while (*line == ' ')
			++line;
		game->img.C = ft_strdup(line);
	}
}

void texture_parsing(t_game *game, char **map)
{
	int i;

	i = 0;
	nullify_struct_members(game);
	while (i < 6)
		check_texture(game, map[i++]);
	if (!game->img.EA || !game->img.NO || !game->img.WE || !game->img.NO)
		error("invaild file", NULL);
}

void parse_map(t_game *game)
{
	char **new_map;
	int i;
	int j;
	int max_len;
	int	temp;

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
