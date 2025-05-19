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
# define OPEN_PIPE	"There is opened pipe"
# define OPEN_QUOTE	"There is opened quote"
# define NO_VALID	"Nope";

# define ERROR	-1
# define OK		0
# define END	1

typedef enum	e_flag
{
	NONE,
	OPEN,
	CLOSE,	
}	t_flag;

typedef enum	e_token_type
{
	CMD,
	OPC,
	REDIR_IN,
	D_QUOTE,
	S_QUOTE,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	ENDOFFILE,
	FILE_PATH,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_flag			flag;
	int				fd[2];
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			*value;
	t_token			*token;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_input
{
	char	*value;
	t_cmd	*cmd;
	int		pipes;
}	t_input;

typedef struct prompt
{
	char	*value;
	char	*cwd;
	char	*user;
	char	*display;
	int		len;
}	t_prompt;

typedef struct minishell
{
	//char		**args; //delete
	t_prompt	*prompt;
	t_input		*input;
}	t_mini;

enum	e_status
{
	E_USAGE = 127,
	E_CTRC	= 130,
	E_UNSTK	= 258
};

extern int	g_status;

/*main*/
int		init_data(t_mini *data);
void	wait_signal(void);
int		set_prompt(t_prompt *promt);
int		set_input(t_mini *data);
void	execute_builtins(t_mini *data, char **envp);

/*split_input_utils*/
int		check_input(char *input);
void	append_cmd(t_input *input, t_cmd *new, char *value);

/*check_input_utils*/
bool	redir_error(char *input);
bool	has_opened_quote(char *input);
bool	has_opened_pipe(char *input);
bool	has_inspected_char(char *input);
bool	has_logic_ops(char *input);
bool	has_wildcard(char *input);

/*free_utils*/
void	free_all(t_mini *data, bool check);
void	free_prompt(t_prompt *prompt, bool check);
void	free_input(t_input *input, bool check);

/*utils*/
int		is_spacetab(int c);
int		is_quote(int c);
int		is_redir(int c);

/*delete*/
void	printf_input(t_input *input);
void	invented_input(t_input *input);

#endif
