#include "minishell.h"

int	g_status;

static int	interactive_mode(t_mini *data, char **envp)
{
	printf("Interactive mode\n");
	while (1)
	{
		if (set_prompt((data)->prompt) != OK)
			check_exit_status(g_status, data);
		if (set_input(data) != OK)
			check_exit_status(g_status, data);
		handle_execution(data->input, envp); // Needs a errors protection
		free_all(data, false);
	}
	return (g_status);
}

static int	redir_mode(t_mini *data, char **envp)
{
	char	*line;

	printf("Redir mode\n");
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (update_status(ERROR));
	data->input->value = ft_strdup("");
	while (line)
	{
		data->input->value = ft_strjoin(data->input->value, line);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	if (ft_strncmp(data->input->value, "\n", 1) == 0)
		return (update_status(OK));
	/*test*/
	printf("input %s\n", data->input->value);
	/*end*/
	if (split_input(data->input) ==  ERROR)
	{
		free_input(data->input, true);
		check_exit_status(g_status, NULL);
	}
	handle_execution(data->input, envp);
	free_input(data->input, true);
	return (g_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	data;

	if (init_data(&data) != OK)
		return (free_all(&data, true), update_status(ERROR));
	wait_signal();
	if (isatty(STDIN_FILENO) && argc == 1)
		interactive_mode(&data, envp);
	else if ((argc > 2 && ft_strncmp(argv[1], "-c", ft_strlen(argv[1])) == 0))
		redir_mode(&data, envp);
	else if ()
		command_mode()
	else
		return ((void)write(STDERR_FILENO, USAGE, 29), update_status(SINTAX));
	return (g_status);
}
