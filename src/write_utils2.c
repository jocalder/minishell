#include "minishell.h"

void	w_not_such(char *value)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, value, ft_strlen(value));
	write(STDERR_FILENO, ": No such file or directory\n", 29);
}

void	w_command_not_found(char *value)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, value, ft_strlen(value));
	write(STDERR_FILENO, ": command not found\n", 21);
}
