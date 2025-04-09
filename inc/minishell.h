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

/*colors*/
# define RED		"\033[0;34m"
# define BLUE		"\033[0;31m"
# define WHITE		"\033[0m"

# define USAGE		"Usage: ./minishell"
# define FAIL_WRITE	"Function write failure"

enum	e_error
{
	CTRC	= 130,
}

extern int g_status;

void	sigint_handler(int signum);
char	*get_prompt(void);

#endif
