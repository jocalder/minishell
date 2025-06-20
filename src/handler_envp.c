#include "minishell.h"

int	create_envp(t_envp *environmnet)
{
	char	*tmp_pwd;
	char	*tmp_cwd;

	/*here*/
	environmnet = ft_calloc(4, sizeof(char *));
	if (data->envp == NULL)
		return (clean_mtx(data->envp), ERROR);
	tmp_pwd = ft_strdup("PWD=");
	if (tmp_pwd == NULL)
		return (clean_mtx(data->envp), ERROR);
	tmp_cwd = getcwd(NULL, 0);
	if (tmp_cwd == NULL)
		return (free(tmp_pwd), clean_mtx(data->envp), ERROR);
	data->envp[0] = ft_strjoin(tmp_pwd, tmp_cwd);
	free(tmp_pwd);
	free(tmp_cwd);
	if (data->envp[0] == NULL)
		return (clean_mtx(data->envp), ERROR);
	data->envp[1] = ft_strdup("SHLVL= 1");
	if (data->envp[1] == NULL)
		return (clean_mtx(data->envp), ERROR);
	data->envp[2] = ft_strdup("_=]");
	if (data->envp[2] == NULL)
		return (clean_mtx(data->envp), ERROR);
	data->envp[3] = NULL;
	return (OK);
}
