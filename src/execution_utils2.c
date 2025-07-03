#include "minishell.h"

void	write_error(t_token *token)
{
	int	i;

	i = 0;
	write(STDERR_FILENO, "minishell: ", 12);
	while (token->next->value[i])
		write(STDERR_FILENO, &token->next->value[i++], 1);
	write(STDERR_FILENO, ": no such file or directory\n", 29);
}

int	open_fd(t_token *token)
{
	int	fd;

	fd = -1;
	if (token->type == APPEND)
		fd = open(token->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(token->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (fd);
}

void	check_pid(t_mini *data, t_cmd *cmd, char **envp)
{
	if (data->pid == -1)
		return ((void)update_status(ERROR));
	if (data->pid == 0)
		return ((void)child_proccess(data, cmd, envp));
	return ;
}
