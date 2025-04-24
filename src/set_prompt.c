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

static char	*replace_home(char *path)
{
	char	*home;
	char	*new_path;

	home = getenv("HOME");
	if (!home)
		return (ft_strdup(path));
	if (home && ft_strncmp(path, home, ft_strlen(home)) == 0)
	{
		new_path = path_empty(path, home);
		if (path[ft_strlen(home)] == '/')
		{
			new_path = ft_calloc((ft_strlen(path) - ft_strlen(home) + 2),
					sizeof(char));
			if (!new_path)
				return (path);
			new_path[0] = '~';
			ft_strcpy(new_path + 1, path + ft_strlen(home));
		}
		return (new_path);
	}
	return (ft_strdup(path));
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

void	set_prompt(t_mini *info)
{
	char	*cwd;

	info->prompt->user = getenv("USER");
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	info->prompt->display = replace_home(cwd);
	free(cwd);
	info->prompt->len = ft_strlen(RED) + ft_strlen(info->prompt->user)
		+ ft_strlen("@minishell") + ft_strlen(WHITE) + ft_strlen(":")
		+ ft_strlen(BLUE) + ft_strlen(info->prompt->display) + ft_strlen(WHITE)
		+ ft_strlen("$ ") + 1;
	info->prompt->prompt = ft_calloc(info->prompt->len, sizeof(char));
	if (!info->prompt->prompt)
		return (free(info->prompt->display));
	info->prompt->ptr = info->prompt->prompt;
	join_prompt(info->prompt->ptr, info->prompt->user, info->prompt->display);
}
