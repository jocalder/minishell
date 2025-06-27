#include "minishell.h"

static int	make_switch(char *path)
{
	printf("cwd: %s\n", getcwd(NULL, 0));
	printf("Path: %s\n", path);
	if (chdir(path) == -1)
		return (ERROR);
	printf("new_cwd: %s\n", getcwd(NULL, 0));
	return (OK);
}

static int	handler_switch(t_mini *data, char *arg)
{
	char	*path;

	path = NULL;
	if ((!arg || !*arg) || (arg && *arg =='~'))
	{
		path = getenv("HOME"); //leak?
		if (!path)
			return (update_status(ERROR));
		if ((!arg || !*arg) || (arg && (*arg == '~' && ft_strlen(arg) == 1)))
			return (update_status(make_switch(path)));
		path = ft_strjoin(path, ++arg);
		if (!path)
			return (update_status(ERROR));
		return (update_status(make_switch(path)));
	}
	else if (ft_strncmp(arg, "-", 2) == 0)
		return(update_status(make_switch(data->oldpwd)));
	else
		return (update_status(make_switch(arg)));
}

static int	update_pwd_oldpwd(t_mini *data)
{
	char *cur_pwd;

	cur_pwd = getcwd(NULL, 0);
	if (!cur_pwd)
		return (update_status(ERROR));
	if (data->oldpwd)
		free(data->oldpwd);
	data->oldpwd = data->pwd;
	data->pwd = cur_pwd;
	return (update_status(OK));
}

/*Must be in parent process*/
/*chdir changes the directory only in the child process*/
int	ft_cd(t_mini *data, t_cmd *cmd)
{
	char	*arg;

	arg = NULL;
	cmd->token = cmd->token->next;
	while (cmd->token && cmd->token->type != ARG)
		cmd->token = cmd->token->next;
	if (cmd->token && cmd->token->type == ARG)
		arg	= cmd->token->value;
	if (cmd->token && (cmd->token->next && cmd->token->next->type == ARG))
	{
		write(STDERR_FILENO, "minishell: cd: too many arguments\n", 30);
		return (update_status(ERROR));
	}
	if (handler_switch(data, arg) != OK)
		return (g_status);
	return (update_pwd_oldpwd(data));
}
