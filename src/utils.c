#include "minishell.h"

bool	unvalidate_bracket(char *str)
{
	int	cur;
	int	end;
	
	if (!str || !*str)
		return (false);
	cur = 0;
	end = ft_strlen(str) - 1;
	while(str[cur])
	{
		if (str[cur] == '[')
		{
			if ((cur == 0 && end > 0) && !is_spacetab(str[cur + 1]))
				return (true);
			else if ((cur > 0 && cur == end) && !is_spacetab(str[cur - 1]))
				return (true);
			else if ((cur > 0 && cur < end)
				&& (!is_spacetab(str[cur - 1]) || (!is_spacetab(str[cur + 1]))))
				return (true);
		}
		cur++;
	}
	return (false);
}
