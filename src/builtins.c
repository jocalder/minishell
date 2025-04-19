#include "minishell.h"

static void	ft_cd(char **args)
{
	char	*home;

	home = NULL;
	if (!args[1])
	{
		home = getenv("HOME");
		if (!home)
			printf("minishell: cd: HOME not set\n");
		if (chdir(home) != 0)
			perror("error home");//change for a similar error message
	}
	else 
	{
		if (chdir(args[1]) != 0)
			perror("error route");//change for a similar error message
	}

}
static void	ft_pwd(void)
{
	char	*cwd;

	cwd = getenv(NULL, 0);
	if (!cwd)
		printf("Mensaje de error que no se cual es");
	printf("%s", cwd);
	free(cwd);
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

void    execute_builtins(t_mini *data, char **envp)
{
    
}