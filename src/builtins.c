#include "minishell.h"

static void	ft_cd(t_mini *data)
{
	char	*home;

	home = NULL;
	if (!data->args[1])
	{
		home = getenv("HOME");
		if (!home)
			printf("minishell: cd: HOME not set\n");
		if (chdir(home) != 0)
			perror("error home");//change for a similar error message
	}
	else
	{
		if (chdir(data->args[1]) != 0)
			perror("error route");//change for a similar error message
	}
}

static void	ft_pwd(void)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
		printf("Mensaje de error que no se cual es");
	else
		printf("%s\n", cwd);
}

static void	ft_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	execute_builtins(t_mini *data, char **envp)
{
	return ;
	if (!data->args || !data->args[0])
		return ;
	//if (ft_strncmp(data->args[0], "echo", 5) == 0)
		//here we should do a function to hanlde the built-in ft_echo(args) or my_echo(args);
	else if (ft_strncmp(data->args[0], "cd", 3) == 0)
		ft_cd(data);
	else if (ft_strncmp(data->args[0], "pwd", 4) == 0)
		ft_pwd();
	//else if (ft_strncmp(data->args[0], "export", 7) == 0)
	//	ft_export();
	//else if (ft_strncmp(data->args[0], "unset", 6) == 0)
	//	ft_unset();
	else if (ft_strncmp(data->args[0], "env", 4) == 0)
		ft_env(envp);
	//else if (ft_strncmp(data->args[0], "exit", 5) == 0)
	//	ft_exit();
	else
		return ;
}
