#include "minishell.h"

void	write_open(unsigned char quote)
{
	write(STDERR_FILENO, ERROR5, 55);
	write(STDERR_FILENO, &quote, 1);
	write(STDERR_FILENO, "\'\n", 2);
	write(STDERR_FILENO, ERROR6, 50);
}
