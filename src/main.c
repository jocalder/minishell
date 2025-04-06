#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv, (void)envp;
	if (argc > 1)
		perror(USAGE);
	/*init_data*/
	g_status = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	/*get_promp*/
	rl_clear_history();
	exit (g_status);
}
