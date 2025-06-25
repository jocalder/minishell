#include "minishell.h"

void	interactive_mode(t_mini *data, char **envp)
{
	while (1)
	{
		wait_signal(0);
		if (set_prompt((data)->prompt) != OK)
			check_exit_status(g_status, data);
		if (set_input(data) == OK)
		{
			if  (handler_execution(data, envp) != OK)
				check_exit_status(g_status, data);
		}
		else
			check_exit_status(g_status, data);
		free_all(data, false);
	}
}

static void	command_mode_one(t_mini *data, char **envp)
{
	char	*line;

	free_prompt(data->prompt, true);
	line = get_next_line(STDIN_FILENO);
	if (!line)
		exit_free(data, ERROR, true);
	data->input->value = ft_strdup("");
	while (line)
	{
		data->input->value = ft_strjoin(data->input->value, line);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	if (ft_strncmp(data->input->value, "\n",
			ft_strlen(data->input->value)) == 0)
		exit_free(data, OK, true);
	if (split_input(data->input) == ERROR)
		exit_free(data, ERROR, true);
	handler_execution(data, envp);
	free_envp(data, true);
	free_input(data->input, true);
}

static void	command_mode_two(t_mini *data, char *arg, char **envp)
{
	free_prompt(data->prompt, true);
	data->input->value = ft_strdup(arg);
	if (split_input(data->input) == ERROR)
		exit_free(data, ERROR, true);
	handler_execution(data, envp);
	free_envp(data, true);
	free_input(data->input, true);
}

void	command_mode(t_mini *data, char **argv, int argc, char **envp)
{
	if (argc == 1)
		command_mode_one(data, envp);
	else if (argc > 2 && ft_strncmp(argv[1], "-c", 3) == 0)
		command_mode_two(data, argv[2], envp);
	else
	{
		free_all(data, true);
		write(STDERR_FILENO, USAGE, 29);
		update_status(SYNTAX);
	}
}
