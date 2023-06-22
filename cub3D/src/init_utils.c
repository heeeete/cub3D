/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:13:36 by huipark           #+#    #+#             */
/*   Updated: 2023/06/22 20:53:23 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_rgb(char *rgb_str)
{
	int	rgb_cnt;
	int	sep_cnt;

	if (!rgb_str)
		error("Error : invaild file", NULL);
	sep_cnt = 0;
	while (*rgb_str)
	{
		rgb_cnt = 0;
		while ((9 <= *rgb_str && *rgb_str <= 13) || (*rgb_str == 32))
			rgb_str++;
		while (ft_isdigit(*rgb_str))
		{
			rgb_cnt++;
			rgb_str++;
		}
		if ((rgb_cnt == 0) || ((*rgb_str != 0) && (*rgb_str != ',') && \
		(9 > *rgb_str || *rgb_str > 13) && (*rgb_str != 32)))
			error("RGB Error : rgb has to have only number", NULL);
		while ((9 <= *rgb_str && *rgb_str <= 13) || (*rgb_str == 32))
			rgb_str++;
		if ((*rgb_str != 0) && (*rgb_str != ','))
			error("RGB Error : there is space between number", NULL);
		else if ((*rgb_str != 0) && (*rgb_str++ == ','))
			sep_cnt++;
	}
	if (sep_cnt != 2)
		error("RGB Error : too many ','", NULL);
}

int	set_rgb(char *rgb_str, int flag) {
	char	*rgb;
	int		ret;

	if (flag == 0)
		rgb = ft_strtok(rgb_str, ",");
	else
		rgb = ft_strtok(NULL, ",");
	if (!rgb)
		error("RGB Error : There should be 3 numbers", NULL);
	ret = ft_atoi(rgb);
	if (ret < 0 || ret > 255)
		error("RGB Error : ranges from 0 to 255", NULL);
	return ret;
}

void read_map(t_game *game, int fd)
{
	char	*line;
	char	*save;
	char	*temp_address;
	int		len;

	len = 0;
	line = get_next_line(fd);
	if (!line)
		error("EMPTY MAP", NULL);
	save = ft_strdup("");
	while (line)
	{
		temp_address = save;
		save = ft_strjoin(save, line);
		free(temp_address);
		free(line);
		line = get_next_line(fd);
	}
	game->map_info.map = ft_split(save, '\n');

	/////////////////////////////////////////////////////////////////
	int i = 0;
	printf("*****************파일 내용******************\n");
	while (game->map_info.map[i])
	{
		int j = 0;
		while (game->map_info.map[i][j])
		{
			printf("%c", game->map_info.map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
	printf("\n\n");
	/////////////////////////////////////////////////////////////////
	while (game->map_info.map[len])
		++len;
	game->map_info.map_height = len - 6;
	free(save);
}

static void	init_player_direction(t_player *player , char c)
{
	if (c == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->planeX = 0.0;
		player->planeY = -0.66;
	}
	else if (c == 'W' )
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->planeX = 0.0;
		player->planeY = 0.66;
	}
	else if (c == 'N')
	{
		player->dir_x = 0.0;
  	 	player->dir_y = -1.0;
		player->planeX = -0.66;
    	player->planeY = 0.0;
	}
	else if (c == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->planeX = 0.66;
		player->planeY = 0.0;
	}
}

static void find_player_direction(t_player *player, char c, int i, int j)
{
	if (c == 'W' || c == 'S' || c == 'N' || c == 'E')
	{
		if (player->x != -1 && player->y != -1)
			error("Error : There must be only one player", NULL);
		player->x = j;
		player->y = i;
		player->player_direction = c;
		init_player_direction(player, c);
	}
}

void check_player_position(char **map, int x, int y)
{
	if (x == -1 && y == -1)
		error("Error : no players", NULL);
	else if (map[y + 1] == NULL || y - 1 == -1)
		error("Error : check player position", NULL);
	else if (map[y][x + 1] == '\0' || x - 1 == -1)
		error("Error : check player position", NULL);
	else if (map[y + 1][x] != '1' && map[y - 1][x] != '1' && map[y + 1][x] != '0' && map[y - 1][x] != '0')
		error("Error : check player position", NULL);
	else if (map[y][x + 1] != '1' && map[y][x - 1] != '1' && map[y][x + 1] != '0' && map[y][x - 1] != '0')
		error("Error : check player position", NULL);
}

void search_map(t_game *game, t_player *player)
{
	int i;
	int j;
	int	prev_line_len;
	char **map;

	i = 0;
	parse_map(game);
	////////////////////////////////////////////
	printf("*****************파싱 결과*************\n\n");
	int a = 0;
	while (game->map_info.map[a])
	{
		int b = 0;
		while (game->map_info.map[a][b])
		{
			printf("%c", game->map_info.map[a][b]);
			b++;
		}
		a++;
		printf("\n");
	}
	printf("FILE PATH : %s\n", game->img.NO);
	printf("FILE PATH : %s\n", game->img.SO);
	printf("FILE PATH : %s\n", game->img.EA);
	printf("FILE PATH : %s\n", game->img.WE);
	printf("F_RGB : %d\n", game->f_rgb.r);
	printf("F_RGB : %d\n", game->f_rgb.g);
	printf("F_RGB : %d\n", game->f_rgb.b);
	printf("C_RGB : %d\n", game->c_rgb.r);
	printf("C_RGB : %d\n", game->c_rgb.g);
	printf("C_RGB : %d\n", game->c_rgb.b);
	printf("PLAYER DIRECTION : %c\n\n", game->player.player_direction);
	printf("*****************************************\n");
	////////////////////////////////////////////
	map = game->map_info.map;
	while (map[i])
	{
		j = 0;
		if (i != 0)
			prev_line_len = ft_strlen(map[i-1]);
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (j > prev_line_len)
					error("Error : map is unvaild", NULL);
				if (i == 0 || j == 0 || i == game->map_info.map_height \
				|| !map[i][j + 1] || map[i][j - 1] == ' ' || map[i][j + 1] == ' ' \
				|| map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
					error("Error : map is unvaild", NULL);
			}
			else if (map[i][j] != '1' && map[i][j] != 'N' && map[i][j] != 'S' \
			&& map[i][j] != 'W' && map[i][j] != 'E' && map[i][j] != ' ')
				error("MAP Error", NULL);
			find_player_direction(player, map[i][j], i, j);
			j++;
		}
		i++;
	}
	check_player_position(game->map_info.map, player->x, player->y);
}
