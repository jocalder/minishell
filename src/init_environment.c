/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_environment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:15:50 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/18 16:32:45 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_envp(t_mini *data)
{
	char	*tmp;
	char	*pwd;

	data->flag = false;
	if (set_new_var(&data->envp, "OLDPWD", count_str(data->envp)) != 0)
		return (update_status(ERROR));
	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (update_status(ERROR));
	pwd = ft_strjoin(ft_strdup("PWD="), tmp);
	if (set_new_var(&data->envp, pwd, count_str(data->envp)) != OK)
		return (update_status(ERROR));
	free(pwd);
	free(tmp);
	tmp = NULL;
	tmp = ft_strjoin(ft_strdup("_="), "/usr/bin/env");
	if (set_new_var(&data->envp, tmp, count_str(data->envp)) != OK)
		return (update_status(ERROR));
	free(tmp);
	return (OK);
}

char	**envpdup(char **envp)
{
	char	**cpy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	cpy = ft_calloc(i + 1, sizeof(char *));
	if (!cpy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		cpy[i] = ft_strdup(envp[i]);
		if (!cpy[i])
		{
			while (i >= 0)
				free(cpy[i--]);
			free(cpy);
			return (NULL);
		}
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

void	get_path(char **path)
{
	char	*cwd;
	char	*user;
	char	*tmp;
	size_t	len;

	*path = ft_strdup("PATH=/home/");
	cwd = getcwd(NULL, 0);
	tmp = cwd + 1;
	while (*tmp && *tmp != '/')
		tmp++;
	tmp++;
	len = 1;
	while (tmp[len] && tmp[len] != '/')
		len++;
	user = ft_substr(tmp, 0, len);
	*path = ft_strjoin(*path, user);
	*path = ft_strjoin(*path, "/bin:/home/");
	*path = ft_strjoin(*path, user);
	*path = ft_strjoin(*path, "/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:");
	*path = ft_strjoin(*path, "/usr/bin:/sbin:/bin:/usr/games:");
	*path = ft_strjoin(*path, "/usr/local/games:/snap/bin");
	return (free(cwd), free(user));
}

int	update_shlvl(t_mini *data)
{
	int		i;
	int		lvl;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (data->exp_vs[++i])
	{
		if (ft_strncmp(data->exp_vs[i], "SHLVL=", 6) == 0)
		{
			lvl = ft_atoi(data->exp_vs[i] + 6);
			free(data->exp_vs[i]);
			tmp = ft_itoa(++lvl);
			if (!tmp)
				return (ERROR);
			data->exp_vs[i] = ft_strjoin(ft_strdup("SHLVL="), tmp);
			if (!data->exp_vs[i])
				return (free(tmp), ERROR);
			return (free(tmp), OK);
		}
	}
	if (!data->exp_vs[i])
		if (set_new_var(&data->exp_vs, "SHLVL=1", i) == ERROR)
			return (ERROR);
	return (OK);
}
