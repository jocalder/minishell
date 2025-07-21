/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_proccess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:47 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:15:47 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	core_heredoc(t_mini *data, t_token **token)
{
	size_t	len;

	len = ft_strlen((*token)->value);
	close((*token)->pipe_hd[0]);
	wait_signal(2);
	while (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "> ", 2);
		(*token)->line = get_next_line(STDIN_FILENO);
		if (!(*token)->line || !*(*token)->line
			|| (ft_strncmp((*token)->line, (*token)->value, len) == 0
				&& (*token)->line[len] == '\n'))
		{
			if ((*token)->line)
				free((*token)->line);
			break ;
		}
		if (!(*token)->flag)
			(*token)->line = expand_content(data, (*token)->line, NULL);
		write((*token)->pipe_hd[1], (*token)->line, ft_strlen((*token)->line));
		free((*token)->line);
	}
	close((*token)->pipe_hd[1]);
	exit (0);
}

static int	close_pipe(t_token **token)
{
	if ((*token)->pipe_hd[0] != -1)
		close((*token)->pipe_hd[0]);
	if ((*token)->pipe_hd[1] != -1)
		close((*token)->pipe_hd[1]);
	(*token)->pipe_hd[0] = -1;
	(*token)->pipe_hd[1] = -1;
	return (update_status(ERROR));
}

int	open_heredoc(t_mini *data, t_token **token)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe((*token)->pipe_hd) < 0)
		return (close_pipe(token));
	pid = fork();
	if (pid < 0)
		return (close_pipe(token));
	if (pid == 0)
		core_heredoc(data, token);
	if (pid > 0)
	{
		close((*token)->pipe_hd[1]);
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (close((*token)->pipe_hd[0]), -1);
		return ((*token)->pipe_hd[0]);
	}
	return (-1);
}
