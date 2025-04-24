#include "minishell.h"

static char	*path_empty(char *path, char *home)
{
	char	*new_path;

	new_path = NULL;
	if (path[ft_strlen(home)] == '\0')
	{
		new_path = ft_calloc(2, sizeof(char));
		if (!new_path)
			return (NULL);
		new_path[0] = '~';
		new_path[1] = '\0';
	}
	return (new_path);
}

static char	*replace_home(char *cwd)
{
	char	*home;
	char	*nwd;

	home = getenv("HOME");
	if (!home)
		return (ft_strdup(cwd));
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		nwd = path_empty(cwd, home);
		if (cwd[ft_strlen(home)] == '/')
		{
			nwd = ft_calloc((ft_strlen(cwd) - ft_strlen(home) + 2),
					sizeof(char));
			if (!nwd)
				return (cwd);
			nwd[0] = '~';
			ft_strcpy(nwd + 1, cwd + ft_strlen(home));
		}
		return (nwd);
	}
	return (ft_strdup(cwd));
}

static void	join_prompt(char *ptr, char *user, char *display)
{
	ft_strcpy(ptr, RED);
	ptr += ft_strlen(RED);
	ft_strcpy(ptr, user);
	ptr += ft_strlen(user);
	ft_strcpy(ptr, "@minishell");
	ptr += ft_strlen("@minishell");
	ft_strcpy(ptr, WHITE);
	ptr += ft_strlen(WHITE);
	ft_strcpy(ptr, ":");
	ptr += ft_strlen(":");
	ft_strcpy(ptr, BLUE);
	ptr += ft_strlen(BLUE);
	ft_strcpy(ptr, display);
	ptr += ft_strlen(display);
	ft_strcpy(ptr, WHITE);
	ptr += ft_strlen(WHITE);
	ft_strcpy(ptr, "$ ");
	free(display);
}

void	set_prompt(t_prompt *prompt)
{
	prompt->user = getenv("USER");
	prompt->cwd = getcwd(NULL, 0);
	if (!prompt->cwd)
		return ;
	prompt->display = replace_home(prompt->cwd);
	free(prompt->cwd);
	prompt->len = ft_strlen(RED) + ft_strlen(prompt->user)
		+ ft_strlen("@minishell") + ft_strlen(WHITE) + ft_strlen(":")
		+ ft_strlen(BLUE) + ft_strlen(prompt->display) + ft_strlen(WHITE)
		+ ft_strlen("$ ") + 1;
	prompt->prompt = ft_calloc(prompt->len, sizeof(char));
	if (!prompt->prompt)
		return (free(prompt->display));
	join_prompt(prompt->prompt, prompt->user, prompt->display);
}
