#include "minishell.h"

static char	*get_env_var(char *var)
{
	char	*env;

	if (!var)
		return (ft_strdup(""));
	env = ft_strdup(getenv(var));
	if (!env)
		env = ft_strdup("");
	return (free(var), env);
}

static char	*handler_expand(char *value, size_t *len)
{
	char	*new_value;

	if (!value)
		return (ft_strdup(""));
	new_value = NULL;
	if (value[*len] == '?')
	{
		new_value = ft_itoa(g_status);
		(*len)++;
	}
	else if (ft_isalpha(value[*len]) || value[*len] == '_')
	{
		while (value[*len]
			&& (value[*len] != '$' && value[*len] != '='
				&& !is_spacetab(value[*len])))
			(*len)++;
		new_value = get_env_var(ft_substr(value, 0, *len));
	}
	else
	{
		(*len)++;
		return (ft_strdup(""));
	}
	return (new_value);
}

char	*expand_content(char *value, t_token *last)
{
	char	*new_value;
	char	*start;
	char	*tmp;
	size_t	len;

	if (!value)
		return (ft_strdup(""));
	if (last && last->type == HEREDOC)
		return (value);
	new_value = ft_strdup("");
	start = value;
	while (*start)
	{
		tmp = NULL;
		len = 0;
		if (*start == '$' && (start[len + 1]
				&& (!is_spacetab(start[len + 1]) && start[len + 1] != '=')))
			tmp = handler_expand(++start, &len);
		else
			tmp = ft_substr(start, 0, ++len);
		start += len;
		new_value = ft_strjoin(new_value, tmp);
		free(tmp);
	}
	return (free(value), new_value);
}
