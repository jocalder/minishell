#include "minishell.h"

int	g_status;

static int	interactive_mode(t_mini *data, char **envp, int argc)
{
	if (isatty(STDIN_FILENO) && argc == 1)
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
	return (OK);
}

static int	redir_mode(t_mini *data, char **argv, int argc, char **envp)
{
	char	*line;

	if ((argc > 2 && ft_strncmp(argv[1], "-c", ft_strlen(argv[1])) == 0))
	{
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
	return (OK);
}

// static int	command_mode(t_mini *data, char **argv, int argc, char **envp)
// {
// 	int		fd_in;
// 	char	*line;

// 	if (argc != 3 || ft_strncmp(argv[1], "-c", 3) != 0)
// 		return (OK);
// 	printf("Command mode\n");
// 	free_prompt(data->prompt, true);
// 	fd_in = open(argv[2], O_RDONLY, 0644);
// 	if (fd_in < 0)
// 		return (update_status(ERROR));
// 	line = get_next_line(fd_in);
// 	if (!line)
// 		return (update_status(ERROR));
// 	data->input->value = ft_strdup("");
// 	while (line)
// 	{
// 		data->input->value = ft_strjoin(data->input->value, line);
// 		free(line);
// 		line = get_next_line(fd_in);
// 	}
// 	if (ft_strncmp(data->input->value, "\n", 1) == 0)
// 		return (update_status(OK));
// 	if (split_input(data->input) ==  ERROR)
// 	{
// 		free_input(data->input, true);
// 		check_exit_status(g_status, NULL);
// 	}
// 	handle_execution(data->input, envp);
// 	free_input(data->input, true);
// 	return (g_status);
// }

// static int	validate_modes(char **argv, int argc)
// {
// 	if (isatty(STDIN_FILENO) && argc == 1)
// 		return (OK);
// 	else if ((argc > 2 && ft_strncmp(argv[1], "-c", 3) == 0))
// 		return (OK);
// 	else if (!isatty(STDIN_FILENO))
// 		return (OK);
// 	else
// 		return (ERROR);
// }

int	main(int argc, char **argv, char **envp)
{
	t_mini	data;

	// if (validate_modes(argv, argc) == ERROR)
	// 	return ((void)write(STDERR_FILENO, USAGE, 29), update_status(SINTAX));
	if (init_data(&data) != OK)
		return (free_all(&data, true), update_status(ERROR));
	wait_signal();
	if (interactive_mode(&data, envp, argc) != OK)
		check_exit_status(g_status, &data);
	// else if (command_mode(&data, argv, argc, envp) != OK)
	// 	check_exit_status(g_status, &data);
	else if (redir_mode(&data, argv, argc, envp) != OK)
		check_exit_status(g_status, &data);
	return (g_status);
}
