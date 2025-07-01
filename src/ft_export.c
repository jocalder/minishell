#include "minishell.h"

static int	count_str(char **envp)
{
	int	i;

	i = 0;
	if (!envp || !*envp)
		return (0);
	while (envp[i])
		i++;
	return (i);
}

static void	sort_exported_vars(char ***p, int size)
{
	char	*tmp;
	bool	swapped;
	int		i;

	if (!p || !*p || !**p || !***p)
		return ;
	tmp = NULL;
	swapped = true;
	while (swapped)
	{
		swapped = false;
		i = 0;
		while (i < (size - 1))
		{
			if (ft_strncmp(p[0][i], p[0][i + 1], ft_strlen(p[0][i]) + 1) > 0)
			{
				tmp = p[0][i];
				p[0][i] = p[0][i + 1];
				p[0][i + 1] = tmp;
				swapped = true;
			}
			i++;
		}
	}
}

static void	print_exported_vars(char **envp)
{
	char	*tmp;

	if (!envp || !*envp || !**envp)
		return ;
	sort_exported_vars(&envp, count_str(envp));
	tmp = NULL;
	while (*envp)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		tmp = ft_strchr(*envp, '=');
		if (tmp)
		{
			write(STDOUT_FILENO, *envp, (ft_strlen(*envp) - ft_strlen(++tmp)));
			write(STDOUT_FILENO, "\"", 1);
			write(STDOUT_FILENO, tmp, ft_strlen(tmp));
			write(STDOUT_FILENO, "\"\n", 2);
		}
		else
		{
			write(STDOUT_FILENO, *envp, ft_strlen(*envp));
			write(STDOUT_FILENO, "\n", 1);
		}
		envp++;
	}
}

/*Must be in parent process*/
/*Variables are being updated only in the child process*/
/*VAR without assigned value, must be printed like VAR*/
int	ft_export(t_mini *data, t_token *token)
{
	char	*builtin;
	int		status;

	builtin = token->value;
	token = token->next;
	while (token && token->type != ARG)
		token = token->next;
	if (token && token->type == ARG && is_option(token->value))
		return (w_builtin_usage(builtin, token->value), update_status(SYNTAX));
	if (!token)
		return ((print_exported_vars(data->cpy_envp)), OK);
	status = 0;
	while (token && token->type == ARG)
	{
		if (!is_validate_id(token->value))
		{
			status = ERROR_FD;
			w_invalid_identifier(builtin, token->value);
			token = token->next;
			continue ;
		}
	}
	return (update_status(status));
}
