/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:57 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:15:57 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mini_user(t_prompt **prompt)
{
	char	*tmp;
	size_t	len;

	if (!prompt || !*prompt)
		return ;
	tmp = (*prompt)->cwd;
	tmp++;
	while (*tmp && *tmp != '/')
		tmp++;
	tmp++;
	len = 1;
	while (tmp[len] && tmp[len] != '/')
		len++;
	(*prompt)->user = ft_substr(tmp, 0, len);
}

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

static char	*replace_home(char *cwd, char **envp)
{
	char	*home;
	char	*nwd;

	home = mini_getenv("HOME", envp);
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

int	set_prompt(t_prompt *prompt, char **envp)
{
	if (!prompt)
		return (update_status(ERROR));
	free_prompt(&prompt, false);
	prompt->cwd = getcwd(NULL, 0);
	if (!prompt->cwd)
		return (update_status(ERROR));
	mini_user(&prompt);
	if (!prompt->user)
		return (update_status(ERROR));
	prompt->display = replace_home(prompt->cwd, envp);
	if (!prompt->display)
		return (update_status(ERROR));
	prompt->len = ft_strlen(RED) + ft_strlen(prompt->user)
		+ ft_strlen("@minishell") + ft_strlen(WHITE)+ ft_strlen(":")
		+ ft_strlen(BLUE) + ft_strlen(prompt->display) + ft_strlen(WHITE)
		+ ft_strlen("$ ") + 1;
	prompt->value = ft_calloc(prompt->len, sizeof(char));
	if (!prompt->value)
		return (update_status(ERROR));
	join_prompt(prompt->value, prompt->user, prompt->display);
	return (OK);
}
