/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:16:17 by jocalder          #+#    #+#             */
/*   Updated: 2025/07/17 20:16:18 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	w_builtin_usage(char *builtin, char *invalid_opt)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, builtin, ft_strlen(builtin));
	write(STDERR_FILENO, ": ", 3);
	if (ft_strncmp(invalid_opt, "--", 2) == 0 && ft_strlen(invalid_opt) > 2)
		write(STDERR_FILENO, "--", 2);
	else
	{
		write(STDERR_FILENO, "-", 1);
		invalid_opt++;
		write(STDERR_FILENO, invalid_opt, 1);
	}
	write(STDERR_FILENO, ": invalid option\n", 18);
	write(STDERR_FILENO, builtin, ft_strlen(builtin));
	write(STDERR_FILENO, ": usage: ", 10);
	write(STDERR_FILENO, builtin, ft_strlen(builtin));
	write(STDERR_FILENO, "\n", 1);
}

void	w_invalid_identifier(char *builtin, char *invalid_id)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, builtin, ft_strlen(builtin));
	write(STDERR_FILENO, ": `", 4);
	write(STDERR_FILENO, invalid_id, ft_strlen(invalid_id));
	write(STDERR_FILENO, "': not a valid identifier\n", 27);
}

void	w_openquote(unsigned char quote)
{
	write(STDERR_FILENO, ERROR5, 55);
	write(STDERR_FILENO, &quote, 1);
	write(STDERR_FILENO, "\'\n", 3);
	write(STDERR_FILENO, ERROR6, 50);
}

void	w_unexpected(int c)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, "syntax error near unexpected token `", 37);
	write(STDERR_FILENO, &c, 1);
	write(STDERR_FILENO, "'\n", 3);
}

void	w_unsupported(char *str)
{
	int		c;

	if (!str)
		return ;
	c = str[0];
	if (ft_strncmp(str, "&&", 2) == 0)
		write(STDERR_FILENO, ERROR7, 52);
	else if (ft_strncmp(str, "||", 2) == 0)
		write(STDERR_FILENO, ERROR2, 52);
	else if (c == '[' && ((ft_strlen(str) - 1) > 0 && !is_spacetab(str[1])))
		write(STDERR_FILENO, ERROR9, 51);
	else if (c == '\\')
		write(STDERR_FILENO, ERROR10, 34);
	else if (str[ft_strlen(str) - 1] != '(' && str[ft_strlen(str) - 1] != ')')
		w_unexpected(c);
	else
		w_unexpected(str[ft_strlen(str) - 1]);
}
