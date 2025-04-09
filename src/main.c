#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*prompt;

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
		free(input);
	}
	rl_clear_history();
	exit (g_status);
}
