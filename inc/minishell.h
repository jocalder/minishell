#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/ioctl.h>

# define USAGE		"Usage: ./minishell"
# define FAIL_WRITE	"Function write failure"
# define RED		"\033[0;34m"
# define BLUE		"\033[0;31m"
# define WHITE		"\033[0m"

typedef enum	e_error
{
	CTRC	= 130,
}	t_status;

extern int	g_status;

void	sigint_handler(int signum);
char    *display_prompt(void);
#endif
