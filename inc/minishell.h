#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/ioctl.h>

# define USAGE		"Usage: ./minishell"
# define FAIL_WRITE	"Function write failure"

typedef enum	e_error
{
	CTRC	= 130,
}	t_status;

extern int	g_status;

void	sigint_handler(int signum);

#endif
