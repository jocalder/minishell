/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:13:14 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/21 12:50:29 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define ERROR11    "minishell: syntax error near unexpected token `<'\n"

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
	VAR,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	bool			flag;
	char			*line;
	int				pipe_hd[2];
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
	bool		flag;
	char		**envp;
	char		**exp_vs;
	char		**vars;
	char		*pwd;
	char		*oldpwd;
	pid_t		pid;
	int			prev_fd;
	int			stdout;
	int			stdin;
}	t_mini;

enum	e_status
{
	SUCH = -3,
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
void	interactive_mode(t_mini *data);
void	command_mode(t_mini *data, char **argv, int argc);

/*init_environment*/
int		mini_envp(t_mini *data);
char	**envpdup(char **envp);
void	get_path(char **path);
int		update_shlvl(t_mini *data);

/*set_structs*/
int		set_prompt(t_prompt *promt, char **envp);
int		set_input(t_mini *data);

/*execution*/
int		handler_execution(t_mini *data, t_cmd *cmd, char **envp);
void	handle_redirections(t_mini *data, t_cmd **cmd);
int		redir_in(t_mini *data, t_cmd *cmd, t_token *token);
int		redir_out(t_cmd *cmd, t_token *token);
int		redir_case(t_cmd *cmd, t_token *next, int *fd);
int		open_fd(t_token *token);
int		check_fd_errors(t_cmd *cmd);
void	close_all_fds(t_mini *data, t_cmd **cmd);
int		handle_fd_errors(t_cmd **cmd);
void	check_pid(t_mini *data, t_cmd *cmd, char **envp);
void	clean_and_close(t_mini *data, t_cmd **cmd);
int		execute_command(t_cmd *cmd, char **envp);
int		builtin_does_not_use_stdin(t_token *token);
int		builtin_does_not_use_stdout(t_token *token);

void	child_proccess(t_mini *data, t_cmd *cmd, char **envp);
void	close_father_fds(t_mini *data, t_cmd **cmd);
void	write_error(t_token *token);
void	handler_dup(t_mini *data, t_cmd **cmd);

int		open_heredoc(t_mini *data, t_token **token);

int		execute_builtin(t_mini *data, t_cmd *cmd);
int		builtin_and_redir(t_mini *data, t_cmd *cmd);

/*built-ins*/
int		ft_echo(t_token *token);
int		ft_pwd(t_token *token, char *pwd);
int		ft_cd(t_mini *data, t_token *token);
int		ft_env(t_token *token, char **envp);
int		ft_export(t_mini *data, t_token *token, char *builtin);
int		ft_unset(t_mini *data, t_token *token);
int		ft_exit(t_mini *data, t_token *token);

/*split_input*/
int		split_input(t_mini *data, t_input *input);
int		validate_pipe(t_input *input, char **str);
int		new_cmd(t_cmd **new, char *start, size_t *len);
void	append_cmd(t_input *input, t_cmd **new, char *value);

/*split_cmd*/
int		split_cmd(t_mini *data, t_cmd **cmd);
void	append_token(t_cmd *cmd, t_token **new, int type);
int		get_type(t_cmd *cmd, t_token *token, char *value, bool check);
t_token	*last_token(t_token *token);

/*new_token*/
int		new_token(t_mini *data, t_cmd *cmd, t_token **new, char **start);
char	*check_cases(t_mini *data, t_cmd *cmd, char **start, size_t *len);
char	*quote_case(t_mini *data, t_cmd *cmd, char *start, size_t *len);
char	*special_case(t_mini *data, t_cmd *cmd, char *start, size_t *len);
char	*expand_content(t_mini *data, char *value, t_token *last);
char	*get_redir(char **s, size_t *len);
void	set_new_token(t_token **new);

/*status_utils*/
int		update_status(int new_status);
void	check_exit_status(int status, t_mini *data);
void	exit_free(t_mini *data, int status);

/*vars_utils*/
char	*mini_getenv(char *name, char **envp);
int		count_str(char **str);
int		set_new_var(char ***ptr, char *var, int i);
int		set_existing_var(char ***ptr, char *var);
int		unset_var(char ***ptr, char *var, int len);
bool	set_local_var(t_mini *data, t_cmd **cmd, t_token *token);
bool	has_type(t_token *token, t_token_type type);
int		local_case(t_mini *data, t_token *token, char *tmp);

/*bools utils*/
bool	is_spacetab(int c);
bool	is_quote(int c);
bool	is_redir(char *str);
bool	is_special(char *str);
bool	is_supported(char *str, bool flag);
bool	is_builtin(t_token *token);
bool	is_option(char *value);
bool	is_validate_id(char *id);
bool	is_existing_var(char **ptr, char *var);
bool	is_same_var(char *compared, char *var);

/*write_utils*/
void	w_openquote(unsigned char quote);
void	w_unsupported(char *str);
void	w_unexpected(int c);
void	w_builtin_usage(char *builtin, char *invalid_opt);
void	w_invalid_identifier(char *builtin, char *invalid_id);
void	w_not_such(char *value);
void	w_command_not_found(char *value);
void	w_unexpected_redir(char *str);
void	w_parse_execution(t_cmd *cmd);

/*free_utils*/
void	free_all(t_mini *data, bool check);
void	free_envp(t_mini *data, bool check);
void	free_prompt(t_prompt **prompt, bool check);
void	free_input(t_input **input, bool check);

#endif
