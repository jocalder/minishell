#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/time.h>

# define USAGE	"Usage: ./minishell"

void	mini_signal_handler(int signum, siginfo_t *info, void *unused);

#endif
