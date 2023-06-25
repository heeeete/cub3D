NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
OPT = -g -fsanitize=address
MFLAGS 	= -L ./mlx -lmlx -framework OpenGL -framework AppKit

LIBFT_DIR = ./Libft
LIBFT_FLAG = -L$(LIBFT_DIR) -lft

SRCS_DIR = ./src/
INIT_DIR = $(SRCS_DIR)init/
GNL_DIR = $(SRCS_DIR)gnl/
KEY_PRESS_DIR = $(SRCS_DIR)key_press/

SRCS = $(SRCS_DIR)main.c \
		$(SRCS_DIR)draw.c \
		$(SRCS_DIR)utils.c \
		$(SRCS_DIR)raycasting.c \
		$(GNL_DIR)get_next_line.c \
		$(GNL_DIR)get_next_line_utils.c \
		$(KEY_PRESS_DIR)key_press_move.c \
		$(KEY_PRESS_DIR)key_press_rotate.c \
		$(INIT_DIR)parse.c \
		$(INIT_DIR)init.c \
		$(INIT_DIR)init_utils.c \
		$(INIT_DIR)init_map.c \
		$(INIT_DIR)init_rgb.c \
		$(INIT_DIR)init_texture.c \

DEPS_DIR = ./include/
DEPS = $(DEPS_DIR)cub3d.h \
		$(DEPS_DIR)get_next_line.h

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(DEPS)
	@make bonus -s -C $(LIBFT_DIR)
	@make -s -C ./mlx
	@${CC} ${CFLAGS} $(MFLAGS) $(OPT) $(SRCS) $(LIBFT_FLAG) -o ${NAME}


clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) -s clean
	@$(MAKE) -C ./mlx -s clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C ./mlx clean

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
