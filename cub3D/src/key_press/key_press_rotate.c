/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpark <jimpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:54:17 by jimpark           #+#    #+#             */
/*   Updated: 2023/06/26 15:16:16 by jimpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

void	press_left(t_player *player)
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	rot_speed;

	rot_speed = player->rot_speed;
	dir_x = player->dir_x;
	dir_y = player->dir_y;
	player->dir_x = dir_x * cos(-rot_speed) - dir_y * sin(-rot_speed);
	player->dir_y = dir_x * sin(-rot_speed) + dir_y * cos(-rot_speed);
	plane_x = player->plane_x;
	plane_y = player->plane_y;
	player->plane_x = plane_x * cos(-rot_speed) - plane_y * sin(-rot_speed);
	player->plane_y = plane_x * sin(-rot_speed) + plane_y * cos(-rot_speed);
}

void	press_right(t_player *player)
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	rot_speed;

	rot_speed = player->rot_speed;
	dir_x = player->dir_x;
	dir_y = player->dir_y;
	player->dir_x = dir_x * cos(rot_speed) - dir_y * sin(rot_speed);
	player->dir_y = dir_x * sin(rot_speed) + dir_y * cos(rot_speed);
	plane_x = player->plane_x;
	plane_y = player->plane_y;
	player->plane_x = plane_x * cos(rot_speed) - plane_y * sin(rot_speed);
	player->plane_y = plane_x * sin(rot_speed) + plane_y * cos(rot_speed);
}
