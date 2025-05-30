#include "minishell.h"

static char	*get_special_var(int c)
{
	if (c == '$')
		return (ft_itoa((int)getpid()));
	else if (c == '?')
		return (ft_itoa(g_status));
	return (NULL);
}

//Maybe add a string with "\n" in line 18 or 21
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
	if (value[*len] == '$' || value[*len] == '?')
		new_value = get_special_var(value[(*len)++]);
	else
	{
		while (value[*len] && value[*len] != '$')
			(*len)++;
		new_value = get_env_var(ft_substr(value, 0, *len));
	}
	return (new_value);
}

char	*expand_content(char *value, int pre_type)
{
	char	*new_value;
	char	*start;
	char	*tmp;
	size_t	len;

	if (!value)
		return (ft_strdup(""));
	if (pre_type == HEREDOC)
		return (value);
	new_value = ft_strdup("");
	start = value;
	while (*start)
	{
		tmp = NULL;
		len = 0;
		if (*start == '$' && (start[len + 1] && !is_spacetab(start[len + 1])))
			tmp = handler_expand(++start, &len);
		else
			tmp = ft_substr(start, 0, ++len);
		start += len;
		new_value = ft_strjoin(new_value, tmp);
		free(tmp);
	}
	return (free(value), new_value);
}
