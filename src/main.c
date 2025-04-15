#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*prompt;
	char	**args;

	(void)argv, (void)envp;
	if (argc > 1)
		perror(USAGE);
	g_status = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt = get_prompt();
		input = readline(prompt);
		free(prompt);
		if (!input)
			return (1);
		if (*input)
			add_history(input);
		args = ft_split(input, ' ');
		//here a split modified to handle the quotes;
		execute_builtin(args);
		//here a function to free the ft_split modified;
		free(input);
	}
	rl_clear_history();
	exit (g_status);
}
