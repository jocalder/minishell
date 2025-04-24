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
# define FAIL_ALLOC	"Memory allocation failure"
# define FAIL_WRITE	"Function write failure"

typedef struct s_redir
{
	bool		redir_input;
	bool		heredoc;
	bool		redir_output;
	bool		append;
	int			fd[2];
	char		*eof;
	char		*file;
	char		*path;
}	t_redir;

typedef struct s_arr
{
	char 			*str;
	bool			s_quote;
	bool			d_quote;
	bool			check_close;
	struct s_arr	*next;
}	t_arr;

typedef struct s_cmd
{
	char			*cmd;
	t_arr			*arr;
	t_redir			*type;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_input
{
	char	*input;
	t_cmd	*cmd;
	int		pipes;
}	t_input;

typedef struct prompt
{
	char	*prompt;
	char	*user;
	char	*display;
	char	*ptr;
	int		len;
}	t_prompt;

typedef struct minishell
{
	char		**args;
	t_input		*input;
	t_prompt	*promt;
}	t_mini;

enum	e_status
{
	CTRC	= 130,
};

extern int	g_status;

void	sigint_handler(int signum);
void	set_prompt(t_mini *data);
void	execute_builtins(t_mini *data, char **envp);

#endif
