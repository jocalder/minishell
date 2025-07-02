#include "minishell.h"

void    write_error(t_token *token)
{
    int i;

    i = 0;
    write(STDERR_FILENO, "minishell: ", 12);
	while (token->next->value[i])
		write(STDERR_FILENO, &token->next->value[i++], 1);
	write(STDERR_FILENO, ": no such file or directory\n", 29);
}