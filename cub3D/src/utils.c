#include "../include/cub3d.h"

#define RED "\033[0;31m"
#define RESET "\033[0m"

void	*wrap_malloc(size_t s)
{
	void	*ret;

	ret = malloc(s);
	if (ret == NULL)
		error ("MALLOC ERROR", NULL);
	return (ret);
}

void	error(char *msg, char *msg2) {
	if (msg2)
		printf("\"%s\" %s\n", msg2, msg);
	else
		printf("%s%s%s\n", RED,msg,RESET);
	exit(1);
}

int exit_game()
{
	exit(0);
}
