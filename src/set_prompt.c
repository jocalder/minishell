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
				return (NULL);
			nwd[0] = '~';
			ft_strcpy(nwd + 1, cwd + ft_strlen(home));
		}
		return (nwd);
	}
	return (ft_strdup(cwd));
}

static void	join_prompt(char *prompt, char *user, char *display)
{
	ft_strcpy(prompt, RED);
	prompt += ft_strlen(RED);
	ft_strcpy(prompt, user);
	prompt += ft_strlen(user);
	ft_strcpy(prompt, "@minishell");
	prompt += ft_strlen("@minishell");
	ft_strcpy(prompt, WHITE);
	prompt += ft_strlen(WHITE);
	ft_strcpy(prompt, ":");
	prompt += ft_strlen(":");
	ft_strcpy(prompt, BLUE);
	prompt += ft_strlen(BLUE);
	ft_strcpy(prompt, display);
	prompt += ft_strlen(display);
	ft_strcpy(prompt, WHITE);
	prompt += ft_strlen(WHITE);
	ft_strcpy(prompt, "$ ");
}

int	set_prompt(t_prompt *prompt)
{
	if (!prompt)
		return (ERROR);
	prompt->user = getenv("USER");
	if (!prompt->user)
		return (ERROR);
	prompt->cwd = getcwd(NULL, 0);
	if (!prompt->cwd)
		return (ERROR);
	prompt->display = replace_home(prompt->cwd);
	if (!prompt->display)
		return (free(prompt->cwd), ERROR);
	prompt->len = ft_strlen(RED) + ft_strlen(prompt->user)
		+ ft_strlen("@minishell") + ft_strlen(WHITE) + ft_strlen(":")
		+ ft_strlen(BLUE) + ft_strlen(prompt->display) + ft_strlen(WHITE)
		+ ft_strlen("$ ") + 1;
	prompt->value = ft_calloc(prompt->len, sizeof(char));
	if (!prompt->value)
		return (free(prompt->display), ERROR);
	join_prompt(prompt->value, prompt->user, prompt->display);
	return (OK);
}
