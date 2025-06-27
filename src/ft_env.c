#include "minishell.h"

/*Must be in parent process*/
/*Variables are being updated only in the child process*/
int	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			write(STDOUT_FILENO, envp[i], ft_strlen(envp[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		i++;
	}
	return (update_status(OK));
}
