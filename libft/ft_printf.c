/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:42:47 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/01/17 21:35:15 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_fd(char ch, int fd)
{
	write(fd, &ch, 1);
	return (1);
}

int	ft_putstr_fd(char *str, int fd)
{
	int	counts_;

	counts_ = 0;
	if (!str)
	{
		write(fd, "(null)", 6);
		return (counts_ += 6);
	}
	while (*str)
	{
		counts_ += ft_putchar_fd(*str, fd);
		str++;
	}
	return (counts_);
}

static int	conver_type(va_list args, char const *format, int fd)
{
	int	counts_;

	counts_ = 0;
	if (*format == 'c')
		return (counts_ += ft_putchar_fd(va_arg(args, int), fd));
	else if (*format == 's')
		return (counts_ += ft_putstr_fd(va_arg(args, char *), fd));
	else if (*format == 'p')
		return (counts_ += ft_putptr_fd(va_arg(args, void *), fd));
	else if (*format == 'd' || *format == 'i')
		return (counts_ += ft_putnbr_fd(va_arg(args, int), fd));
	else if (*format == 'u')
		return (counts_ += ft_putunsnbr_fd(va_arg(args, unsigned int), fd));
	else if (*format == 'x' || *format == 'X')
	{
		counts_ += ft_puthex_fd(va_arg(args, unsigned int), *format, fd);
		return (counts_);
	}
	else if (*format == '%')
		return (counts_ += ft_putchar_fd('%', fd));
	else
		return (-1);
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		counts;

	counts = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			counts += conver_type(args, format, 1);
			if (counts == -1)
			{
				va_end(args);
				return (-1);
			}
		}
		else
			counts += ft_putchar_fd(*format, 1);
		format++;
	}
	va_end(args);
	return (counts);
}

int	ft_printf_fd(int fd, char const *format, ...)
{
	va_list	args;
	int		counts;

	counts = 0;
	va_start(args, format);
	if (fd >= 0)
	{
		while (*format)
		{
			if (*format == '%')
			{
				format++;
				counts += conver_type(args, format, fd);
				if (counts == -1)
					return (-1);
			}
			else
				counts += ft_putchar_fd(*format, fd);
			format++;
		}
	}
	va_end(args);
	return (counts);
}
