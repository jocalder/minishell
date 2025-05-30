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
# include <sys/wait.h>

/*colors*/
# define RED				"\033[0;34m"
# define BLUE				"\033[0;31m"
# define WHITE				"\033[0m"

# define USAGE			"Usage: ./minishell"

# define ERROR1	"minishell: syntax error near unexpected token `|'"
# define ERROR2	"minishell: syntax error near unexpected token `||'"
# define ERROR3	"minishell: syntax error near unexpected token `>'"

# define CMD_NO_FOUND	"Command not found"

# define ERROR	-1
# define OK		0
# define END	1

typedef enum	e_token_type
{
	CMD,
	ARG,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	ENDOFFILE,
	FILE_PATH,
	BUILTIN,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	char			*value;
	t_token			*token;
	int				fd[2];
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_input
{
	char	*value;
	t_cmd	*cmd;
	int		pipes;
}	t_input;

typedef struct s_prompt
{
	char	*value;
	char	*cwd;
	char	*user;
	char	*display;
	int		len;
}	t_prompt;

typedef struct minishell
{
	t_prompt	*prompt;
	t_input		*input;
}	t_mini;

enum	e_status
{
	E_USAGE = 127,
	E_CTRC	= 130,
	E_UNSTK	= 2
};

extern int	g_status;

int		init_data(t_mini *data);
void	wait_signal(void);
int		set_prompt(t_prompt *promt);
int		set_input(t_mini *data);
void	execute_builtins(t_mini *data, char **envp);

/*split_input*/
int		split_input(t_input *input);
int		validate_pipe(t_input *input, char **str);
t_cmd	*new_cmd(char *start, size_t *len);
void	append_cmd(t_input *input, t_cmd *new, char *value);

/*split_cmd*/
int		split_cmd(t_cmd **cmd);
void	append_token(t_cmd *cmd, t_token **new, int type);
char	*expand_content(char *value);
int		get_type(t_token *token, char *value);
char	*get_redir(char **str, size_t *len);

/*status_utils*/
int		update_status(int new_status);
void	exit_status(int status, t_mini *data);

/*utils*/
int		is_spacetab(int c);
int		is_quote(int c);
int		is_redir(char *str);

/*free_utils*/
void	free_all(t_mini *data, bool check);
void	free_prompt(t_prompt *prompt, bool check);
void	free_input(t_input *input, bool check);

/*utils*/
int		is_spacetab(int c);
int		is_quote(int c);
int		update_status(int new_status);
bool	is_builtin(char *value);

/*delete*/
void	printf_input(t_input *input);
void	invented_input(t_input *input);

/*execution*/
void    handle_execution(t_mini *data, char **envp);
void	ft_child_proccess(int pipe_fd[2], int prev_fd, t_cmd *cmd, char **envp);
int		redir_in(t_token *token);
int		redir_out(t_token *token);
void	execute_command(t_cmd *cmd, char **envp);
int		execute_builtin(t_mini *data, t_cmd *cmd, char **envp);
void	wait_all(void);
int		open_heredoc(char *delimiter);

#endif
