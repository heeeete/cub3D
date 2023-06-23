#ifndef CUB3D_H
#define CUB3D_H

#include "get_next_line.h"
#include "../mlx/mlx.h"
#include "../Libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#define SIZE 64

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_release		3
#define X_EVENT_KEY_EXIT		17 //exit key code

#define KEY_ESC			53
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_LEFT_ARROW 123
# define KEY_RIGHT_ARROW 124

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;

	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
}				t_img;

typedef struct	s_rgb
{
	int	r;
	int	g;
	int	b;
	int	rgb;
}				t_rgb;

typedef struct	s_map
{
	char	**map;
	char	**int_map;
	int		**buf;
	int		**texture;
	int		re_buf;
	int		map_height;
	int		max_width;
}				t_map;

typedef struct s_playsr
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		planeX;
	double		planeY;
	double		move_speed;
	double		rot_speed;
	char	player_direction;
}				t_player;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_map		map_info;
	t_player	player;
	t_rgb		f_rgb;
	t_rgb		c_rgb;
}				t_game;

//utils.c
void	error(char *msg, char *msg2);
void	*wrap_malloc(size_t s);
int		exit_game(void);
int	check_format(char *str);

//parse.c
void	check_texture(t_game *game, char *line);
void	texture_parsing(t_game *game, char **map);
void	 parse_map(t_game *game);

//init.c
void nullify_struct_members(t_game *game);
void init(t_game *game, char *argv);
void init_rgb(t_game *game);

//init_utils.c
int	check_map_error(char c);
int	check_invalid_map(int i, int j, int prev_line_len, t_game *game);
void	check_player_position(char **map, int x, int y);
void	find_player_direction(t_player *player, char c, int i, int j);
void	init_player_direction(t_player *player, char c);

//key_press_utils.c
int key_press(int key, t_game *game);
void	press_w(t_game *game);
void	press_s(t_game *game);
void	press_a(t_game *game);
void	press_d(t_game *game);
void press_right(t_player *player);
void press_left(t_player *player);

//raycasting.c
int main_loop(t_game *game);

//init_map.c
void init_int_map(t_game *game);
void init_game_map(t_game *game);

//init_texture.c
void	init_texture(t_game *game);

//init_rgb.c
void	init_rgb(t_game *game);


#endif
