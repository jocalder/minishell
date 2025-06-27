#include "minishell.h"

static int	switch_to_root(void)
{
	//
}

static int	handler_path(char *builtin, char *arg)
{
	if (!arg || !*arg)
		return(update_status(switch_to_root()));
	//
	return (OK);
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

int	ft_cd(t_mini *data, t_cmd *cmd)
{
	char	*builtin;
	char	*arg;

	builtin = cmd->token->value;
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
	if (handler_path(builtin, arg) != OK)
		return (g_status);
	return (update_pwd_oldpwd(data));
}
