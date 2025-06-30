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
# include <termios.h>

/*colors*/
# define RED		"\001\033[0;34m\002"
# define BLUE		"\001\033[0;31m\002"
# define WHITE		"\001\033[0m\002"

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

typedef enum e_token_type
{
	CMD,
	ARG,
	REDIR_IN,
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
	bool			flag;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	char			*value;
	t_token			*token;
	int				fd_in;
	int				fd_out;
	int				pipe_fd[2];
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
	char		**cpy_envp;
	char		*pwd;
	char		*oldpwd;
	pid_t		pid;
	int			prev_fd;
}	t_mini;

enum	e_status
{
	ERROR_FD = -2,
	ERROR = -1,
	SYNTAX	= 2,
	NOTEXEC = 126,
	NOTFOUND = 127,
	CTRC	= 130,
};

extern int	g_status;

void	init_data(t_mini *data, char **envp);
void	wait_signal(int i);
void	interactive_mode(t_mini *data, char **envp);
void	command_mode(t_mini *data, char **argv, int argc, char **envp);

/*init_environment*/
char	**envpdup(char **envp);
int		update_envp(t_mini *data);

/*set_structs*/
int		set_prompt(t_prompt *promt);
int		set_input(t_mini *data);

/*execution*/
int		handler_execution(t_mini *data, char **envp);
void	close_all_fds(t_mini *data, t_cmd **cmd);
int		child_proccess(t_mini *data, t_cmd *cmd, char **envp);
int		execute_command(t_cmd *cmd, char **envp);
int		execute_builtin(t_mini *data, t_cmd *cmd);
int		open_heredoc(char *delimiter);

/*built-ins*/
int		ft_echo(t_cmd *cmd);
int		ft_pwd(t_cmd *cmd, char *pwd);
int		ft_cd(t_mini *data, t_cmd *cmd);
int		ft_env(char **envp);
int		ft_exit(t_mini *data, t_cmd *cmd);

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
char	*check_cases(t_cmd *cmd, t_token *new, char **start, size_t *len);
char	*quote_case(t_cmd *cmd, char *start, size_t *len);
char	*special_case(t_cmd *cmd, char *start, size_t *len);
char	*expand_content(char *value, t_token *last);
char	*get_redir(char **s, size_t *len);

/*status_utils*/
int		update_status(int new_status);
void	check_exit_status(int status, t_mini *data);
void	exit_free(t_mini *data, int status);

/*bools utils*/
bool	is_spacetab(int c);
bool	is_quote(int c);
bool	is_redir(char *str);
bool	is_special(char *str);
bool	is_supported(char *str, bool flag);
bool	is_validate_bracket(char *str);
bool	is_builtin(t_token *token);
bool	is_option(char *value);

/*write_utils*/
void	w_openquote(unsigned char quote);
void	w_unsupported(char *str);
void	w_unexpected(int c);
void	w_builtin_usage(char *builtin, char *invalid_opt);

/*free_utils*/
void	free_all(t_mini *data, bool check);
void	free_envp(t_mini *data, bool check);
void	free_prompt(t_prompt *prompt, bool check);
void	free_input(t_input *input, bool check);

#endif
