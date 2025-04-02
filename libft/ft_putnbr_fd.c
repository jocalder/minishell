/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:47:43 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/17 21:33:00 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbrfd(int n, int fd)
{
	if (fd >= 0)
	{
		if (n == -2147483648)
			ft_putstrfd("-2147483648", fd);
		else if (n < 0)
		{
			ft_putcharfd('-', fd);
			ft_putnbrfd(-n, fd);
		}
		else if (n > 9)
		{
			ft_putnbrfd(n / 10, fd);
			ft_putcharfd((n % 10) + '0', fd);
		}
		else
			ft_putcharfd(n + '0', fd);
	}
}
