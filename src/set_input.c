#include "minishell.h"

// static void	count_pipes(char *input, int *pipes)
// {
// 	long	result;
// 	char	quote;

// 	while (*input)
// 	{
// 		while (*input && is_spacetab(*input))
// 			input++;
// 		if ()
// 		input++;
// 	}
// }

// static t_cmd	**split_input(t_input *input)
// {
// 	//
// }

int	set_input(t_mini *data)
{
	if (!data)	
		return (ERROR);
	data->input->value = readline(data->prompt->value);
	if (!data->input->value)
		return (END);
	if (data->input->value && *(data->input->value))
		add_history(data->input->value);
	/*new_branch*/
	data->input->cmd = split_input(data);
	if (!data->input->cmd && !*(data->input->value))
		return (ERROR);
	/*old_branch*/
	//data->args = ft_split(data->input->value, ' ');
	printf_input(data->input);
	return (OK);
}
