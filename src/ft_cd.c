#include "minishell.h"

static int	make_switch(char *path)
{
	if (!path)
		return (ERROR);
	if (chdir(path) == -1)
	{
		write(STDERR_FILENO, "minishell: cd: ", 16);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, ": No such file or directory\n", 29);
		return (free(path), ERROR_FD);
	}
	return (free(path), OK);
}

static int	handler_switch(t_mini *data, char *arg)
{
	char	*path;

	path = NULL;
	if ((!arg || !*arg) || (arg && *arg == '~'))
	{
		path = mini_getenv("HOME", data->envp);
		if (!path)
		{
			write(STDOUT_FILENO, "minishell: cd: HOME not set\n", 29);
			return (update_status(ERROR_FD));
		}
		if ((!arg || !*arg) || (arg && (*arg == '~' && ft_strlen(arg) == 1)))
			return (update_status(make_switch(ft_strdup(path))));
		path = ft_strjoin(ft_strdup(path), ++arg);
		if (!path)
			return (update_status(ERROR));
		return (update_status(make_switch(ft_strdup(path))));
	}
	else if (ft_strncmp(arg, "-", 2) == 0 && ft_strchr(data->oldpwd, '='))
		return (update_status(make_switch(ft_strdup(data->oldpwd))));
	else if (ft_strncmp(arg, "-", 2) == 0 && !ft_strchr(data->oldpwd, '='))
		return ((void)write(STDERR_FILENO,
				"minishell: cd: OLDPWD not set\n", 31), ERROR_FD);
	else
		return (update_status(make_switch(ft_strdup(arg))));
}

static int	update_pwd_oldpwd(t_mini *data)
{
	char	*cur_pwd;

	cur_pwd = NULL;
	cur_pwd = getcwd(NULL, 0);
	if (!cur_pwd)
		return (update_status(ERROR));
	if (data->oldpwd)
	{
		free(data->oldpwd);
		data->oldpwd = NULL;
	}
	data->oldpwd = data->pwd;
	data->pwd = cur_pwd;
	return (update_status(OK));
}

int	ft_cd(t_mini *data, t_token *token)
{
	char	*arg;

	arg = NULL;
	token = token->next;
	while (token && token->type != ARG)
		token = token->next;
	if (token && token->type == ARG)
		arg = token->value;
	if (token && (token->next && token->next->type == ARG))
	{
		write(STDERR_FILENO, "minishell: cd: too many arguments\n", 35);
		return (update_status(ERROR));
	}
	if (handler_switch(data, arg) != OK)
		return (g_status);
	return (update_pwd_oldpwd(data));
}
