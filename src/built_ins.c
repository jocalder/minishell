#include "minishell.h"

void	execute_builtin(char **args)
{
	if (!args || !args[0])
		return ;
	if (ft_strncmp(args[0], "echo", 5) == 0)
		//here we should do a function to hanlde the built-in ft_echo(args) or my_echo(args);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		//the same ft_cd(args) or my_cd(args);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		//ft_pwd(args) or my_cd(args);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		//ft_export(args) or my_export(porco);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		//ft_unset(args) or my_unset(putano);
	else if (ft_strncmp(args[0], "env", 4) == 0)
		//ft_env(args) or my_env(args);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		//ft_exit(args) or my_exit(args);
    else
		return ;
}
