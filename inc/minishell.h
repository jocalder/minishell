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
# define RED				"\001\033[0;34m\002"
# define BLUE				"\001\033[0;31m\002"
# define WHITE				"\001\033[0m\002"

# define USAGE		"Usage: ./minishell [-c] ...\n"

/*syntax error*/
# define ERROR1		"minishell: syntax error near unexpected token `|'\n"
# define ERROR2		"minishell: syntax error near unexpected token `||'\n"
# define ERROR3		"minishell: syntax error near unexpected token `>'\n"
# define ERROR4		"minishell: syntax error near unexpected token `newline'\n"

# define ERROR5		"minishell: unexpected EOF while looking for matching `"
# define ERROR6		"minishell: syntax error: unexpected end of file \n"

# define ERROR7 	"minishell: syntax error near unexpected token `&&'\n"
# define ERROR8		"minishell: syntax error near unexpected token `[['\n"
# define ERROR9		"minishell: syntax error near unexpected token `['\n"
# define ERROR10	"minishell: unsupported token '\\'\n"

# define OK		0
# define END	-1

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
	bool			flag;
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
	ERROR = 1,
	SYNTAX	= 2,
	NOTEXEC = 126,
	NOTFOUND = 127,
	CTRC	= 130,
};

extern int	g_status;

int		init_data(t_mini *data);
void	wait_signal(void);
int		set_prompt(t_prompt *promt);
int		set_input(t_mini *data);

/*execution*/
void    handler_execution(t_input *input, char **envp);
void	child_proccess(int pipe_fd[2], int prev_fd, t_cmd *cmd, char **envp);
void	execute_command(t_cmd *cmd, char **envp, char *mode);
int		execute_builtin(t_mini *data, t_cmd *cmd, char **envp);
int		open_heredoc(char *delimiter);

/*split_input*/
int		split_input(t_input *input);
int		validate_pipe(t_input *input, char **str);
int		new_cmd(t_cmd **new, char *start, size_t *len);
void	append_cmd(t_input *input, t_cmd **new, char *value);

/*split_cmd*/
int		split_cmd(t_cmd **cmd);
void	append_token(t_cmd *cmd, t_token **new, int type);
int		get_type(t_token *token, char *value, bool check);
t_token	*last_token(t_token *token);

/*new_token*/
int		new_token(t_cmd *cmd, t_token **new, char **start);
int		check_cases(t_cmd *cmd, char **start, char **tmp, size_t *len);
int		quote_case(t_cmd *cmd, char *start, char **tmp, size_t *len);
void	special_case(t_cmd *cmd, char *start, char **tmp, size_t *len);
char	*expand_content(char *value, t_token *last);
char	*get_redir(char **str, size_t *len);

/*status_utils*/
int		update_status(int new_status);
void	check_exit_status(int status, t_mini *data);

/*bools utils*/
bool	is_spacetab(int c);
bool	is_quote(int c);
bool	is_redir(char *str);
bool	is_special(char *str);
bool	is_supported(char *str);
bool	is_builtin(char *value);
bool	is_validate_bracket(char *str);

/*utils*/
void	w_openquote(unsigned char quote);
void	w_unsupported(char *str);

/*free_utils*/
void	free_all(t_mini *data, bool check);
void	free_prompt(t_prompt *prompt, bool check);
void	free_input(t_input *input, bool check);

/*delete*/
void	printf_input(t_input *input);
void	invented_input(t_input *input);

#endif
