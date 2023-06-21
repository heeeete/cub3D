NAME	= libft.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

FILES 	=		ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_strtok.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c

FILES_BONUS = 	ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c

OBJS		= $(FILES:.c=.o)
OBJS_BONUS 	= $(FILES_BONUS:.c=.o)

AR		= ar -crs
RM		= rm -f

ifdef WITH_BONUS
			OBJECTS	= $(OBJS) $(OBJS_BONUS)
else
			OBJECTS	= $(OBJS)
endif

all		:	$(NAME)

$(NAME)	:	$(OBJECTS)
			$(AR) $(NAME) $(OBJECTS)

bonus	:
			make WITH_BONUS=1 all

clean	:
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean	:	clean
			$(RM) $(NAME)

re		:
			make fclean
			make all
.PHONY	: bonus all clean fclean re
