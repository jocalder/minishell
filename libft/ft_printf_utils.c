/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:37:27 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/25 04:51:06 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int nbr, int fd)
{
	int	counts_;

	counts_ = 0;
	if (nbr == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	else if (nbr < 0)
	{
		counts_ += ft_putchar_fd('-', fd);
		counts_ += ft_putnbr_fd(-nbr, fd);
	}
	else if (nbr > 9)
	{
		counts_ += ft_putnbr_fd((nbr / 10), fd);
		counts_ += ft_putchar_fd((nbr % 10) + '0', fd);
	}
	else
		counts_ += ft_putchar_fd(nbr + '0', fd);
	return (counts_);
}

int	ft_putunsnbr_fd(unsigned int unsnbr, int fd)
{
	int	counts_;

	counts_ = 0;
	if (unsnbr > 9)
	{
		counts_ += ft_putunsnbr_fd((unsnbr / 10), fd);
		counts_ += ft_putchar_fd((unsnbr % 10) + '0', fd);
	}
	else
		counts_ += ft_putchar_fd(unsnbr + '0', fd);
	return (counts_);
}

int	ft_puthex_fd(unsigned long long num, char format, int fd)
{
	char	*base;
	int		counts_;

	counts_ = 0;
	if (format == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (num == 0 && counts_ == 0)
		return (counts_ += ft_putchar_fd('0', fd));
	if (num >= 16)
		counts_ += ft_puthex_fd(num / 16, format, fd);
	counts_ += ft_putchar_fd(base[num % 16], fd);
	return (counts_);
}

int	ft_putptr_fd(void *ptr, int fd)
{
	unsigned long long	p;
	int					counts_;

	counts_ = 0;
	p = (unsigned long long)ptr;
	if (!ptr)
		return (ft_putstr_fd("(nil)", fd));
	counts_ += ft_putstr_fd("0x", fd);
	counts_ += ft_puthex_fd(p, 'x', fd);
	return (counts_);
}
