#include "minishell.h"

static int	validate_numeric_argument(t_token *token)
{
	char	*value;
	int		i;

	value = token->value;
	i = 0;
	while(value[i])
	{
		if (!ft_isdigit(value[i]) && value[i] != '-' && value[i] != '+')
		{
			write(STDERR_FILENO, "minishell: exit: ", 18);
			write(STDERR_FILENO, value, ft_strlen(value));
			write(STDERR_FILENO, ": numeric argument required\n", 29);
			return (update_status(SYNTAX));
		}
		i++;
	}
	return (OK);
}

static int	check_numeric_limits(char *value)
{
	if ((ft_strlen(value) == 19
		&& ft_strncmp(value, "9223372036854775807", 19) > 0)
		|| (ft_strlen(value) == 20
		&& ft_strncmp(value, "-9223372036854775808", 20) > 0)
		|| ft_strlen(value) > 21)
	{
		write(STDERR_FILENO, "minishell: exit: ", 18);
		write(STDERR_FILENO, value, ft_strlen(value));
		write(STDERR_FILENO, ": numeric argument required\n", 29);
		return (update_status(SYNTAX));
	}
	return (OK);
}

static void	set_exit_code(t_token *token)
{
	int	num;

	num = ft_atoi(token->value);
	if (num < 0)
		num = 256 + num;
	update_status(num);
}

/*Must be in parent process*/
int	ft_exit(t_mini *data, t_cmd *cmd)
{
	write(STDOUT_FILENO, "exit\n", 6);
	cmd->token = cmd->token->next;
	if (cmd->token && cmd->token->type == ARG)
	{
		if (validate_numeric_argument(cmd->token) != OK)
			return (g_status);
		if (check_numeric_limits(cmd->token->value) != OK)
			return (g_status);
		if (cmd->token->next && cmd->token->next->type == ARG)
		{
			write(STDERR_FILENO, "minishell: exit: too many arguments\n", 37);
			return (update_status(SYNTAX));
		}
		set_exit_code(cmd->token);
	}
	free_all(data, true);
	rl_clear_history();
	update_status(g_status);
	exit(g_status);
	// kill(data->pid, SIGKILL);
	// return (g_status);
}
