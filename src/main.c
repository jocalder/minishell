#include "minishell.h"

int	g_status;

static int	interactive_mode(t_mini *data, char **envp)
{
	while (1)
	{
		if (set_prompt((data)->prompt) != OK)
			check_exit_status(g_status, data);
		if (set_input(data) != OK)
			check_exit_status(g_status, data);
		handler_execution(data->input, envp);
		free_all(data, false);
	}
	exit (g_status);
}

/*To be finished*/
static void	command_mode(t_mini *data, char **argv, int argc, char **envp)
{
	char	*line;

	if (argc == 1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return ((void)update_status(ERROR));
		data->input->value = ft_strdup("");
		while (line)
		{
			data->input->value = ft_strjoin(data->input->value, line);
			free(line);
			line = get_next_line(STDIN_FILENO);
		}
		if (ft_strncmp(data->input->value, "\n", 1) == 0)
		{
			free_input(data->input, true);
			exit(OK);
		}
		if (split_input(data->input) ==  ERROR)
		{
			free_input(data->input, true);
			check_exit_status(g_status, NULL);
		}
		if (g_status != SYNTAX && argc == 1)
			handler_execution(data->input, envp);
		free_input(data->input, true);
	}
	else if (argc > 2 && ft_strncmp(argv[1], "-c", ft_strlen(argv[1])) == 0)
	{
		data->input->value = ft_strdup(argv[2]);
		split_input(data->input);
		handler_execution(data->input, envp);
		free_input(data->input, true);
	}
	else
	{
		free_input(data->input, true);
		(void)write(STDERR_FILENO, USAGE, 29), update_status(SYNTAX);
		exit(SYNTAX);
	}
	exit (g_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	data;

	(void)argv;
	if (init_data(&data) != OK)
		return (free_all(&data, true), update_status(ERROR));
	wait_signal();
	if (isatty(STDIN_FILENO) && argc == 1)
		interactive_mode(&data, envp);
	else // if (!isatty(STDIN_FILENO))
		command_mode(&data, argv, argc,envp);
	exit (g_status);
}
