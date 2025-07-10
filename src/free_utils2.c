#include "minishell.h"

static void	update_underscore(t_mini *data)
{
	t_cmd	*cmd;
	t_token	*token;
	char	*tmp;

	if (!data || !data->input || !data->input->cmd
		|| g_status != OK)
		return ;
	cmd = data->input->cmd;
	while (cmd->next)
		cmd = cmd->next;
	token = cmd->token;
	while (token->next
		&& (token->next->type == CMD || token->next->type == ARG))
		token = token->next;
	tmp = ft_strjoin(ft_strdup("_="), token->value);
	if (!tmp)
		exit_free(data, ERROR);
	if (is_existing_var(data->exp_vs, "_"))
		set_existing_var(&data->exp_vs, tmp);
	else
		set_new_var(&data->exp_vs, tmp, count_str(data->exp_vs));
	free(tmp);
}

void	free_envp(t_mini *data, bool check)
{
	if (!data)
		return ;
	if (!check)
	{
		update_underscore(data);
		return ;
	}
	if (data->envp)
		free_array(data->envp, -1);
	if (data->exp_vs)
		free_array(data->exp_vs, -1);
	if (data->vars)
		free_array(data->vars, -1);
	if (data->pwd)
		free(data->pwd);
	if (data->oldpwd)
		free(data->oldpwd);
	data->envp = NULL;
	data->exp_vs = NULL;
	data->vars = NULL;
	data->pwd = NULL;
	data->oldpwd = NULL;
}
