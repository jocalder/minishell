#include "minishell.h"

int	is_spacetab(int c)
{
	if (c >= 9 && c <= 13 || c == 32)
		return (1);
	return (0);
}
