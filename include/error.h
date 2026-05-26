#ifndef ERROR_H
# define ERROR_H

# include "../libft/include/libft.h"
# include <unistd.h>

int	syntax_error(char *msg);
int	malloc_error(void);
int	print_syntax_error(char *msg);

#endif