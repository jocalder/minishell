#include "minishell.h"

// // static void	count_pipes(char *input, int *pipes)
// // {
// // 	long	result;
// // 	char	quote;

// // 	while (*input)
// // 	{
// // 		while (*input && is_spacetab(*input))
// // 			input++;
// // 		if ()
// // 		input++;
// // 	}
// // }

// static t_cmd	**split_input(t_input *input)
// {
// 	if (!input || !(input->value))
// 		return (NULL);
// 	if (check_errors(input->value) == ERROR)
// 		return (NULL);
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
	// if (!*(data->input->value))
	// 	return (OK);
	// data->input->cmd = split_input(data);
	// if (!data->input->cmd)
	// 	return (ERROR);
	/*old_branch*/
	//data->args = ft_split(data->input->value, ' ');
	/*invented_input*/ /*choose a number of case (1 ~ 3)*/
	invented_input(data->input);
	printf_input(data->input);
	return (OK);
}
