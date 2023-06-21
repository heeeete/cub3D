CC = cc
# CFLAGS = -Wall -Wextra -Werror
OPT = -g -fsanitize=address
MFLAGS 	= -L ./mlx -lmlx -framework OpenGL -framework AppKit

NAME = cub3D
SRCS_DIR = ./src/
SRCS = $(SRCS_DIR)main.c \
		$(SRCS_DIR)get_next_line.c \
		$(SRCS_DIR)get_next_line_utils.c \
		$(SRCS_DIR)utils.c \
		$(SRCS_DIR)parse.c \
		$(SRCS_DIR)init.c \
		$(SRCS_DIR)init_utils.c

DEPS_DIR = ./include/
DEPS = $(DEPS_DIR)cub3d.h \
		$(DEPS_DIR)get_next_line.h

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):$(OBJS) $(DEPS)
	@make -s bonus -C libft
	@mv libft/libft.a ./
	${CC} ${CFLAGS} $(MFLAGS) $(OPT) $(SRCS) libft.a -o ${NAME}
	install_name_tool -change libmlx.dylib @executable_path/mlx/libmlx.dylib $@

clean:
	rm -f $(OBJS)
	make -s clean -C libft

fclean: clean
	rm -f $(NAME)
	rm -f libft.a
	make -s clean -C libft

re: fclean all

.PHONY: all clean fclean re
