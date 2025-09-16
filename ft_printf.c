/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:12:49 by pbongiov          #+#    #+#             */
/*   Updated: 2025/08/16 19:15:02 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static int	printstr(char *str)
{
	int	n;

	if (!str)
		return (write(1, "(null)", 6));
	n = 0;
	while (str[n])
		n++;
	return (write(1, str, n));
}

static int	ft_hexa(unsigned long long num, char *base, unsigned int b)
{
	int	i;

	i = 0;
	if (num >= b)
		i += ft_hexa(num / b, base, b);
	return (i + write(1, &base[num % b], 1));
}

static int	ft_putnbr(int n)
{
	char			c;
	int				i;
	unsigned int	num;

	i = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		num = -n;
		i++;
	}
	else
	{
		num = n;
	}
	if (num >= 10)
		i += ft_putnbr(num / 10);
	c = num % 10 + '0';
	return (i + write(1, &c, 1));
}

static int	ft_conditions(char c, va_list ap)
{
	unsigned long	p;

	if (c == 's')
		return (printstr(va_arg(ap, char *)));
	else if (c == 'c')
		return (write(1, &((char){va_arg(ap, int)}), 1));
	else if (c == 'i' || c == 'd')
		return (ft_putnbr(va_arg(ap, int)));
	else if (c == 'X')
		return (ft_hexa(va_arg(ap, unsigned int), "0123456789ABCDEF", 16));
	else if (c == 'x')
		return (ft_hexa(va_arg(ap, unsigned int), "0123456789abcdef", 16));
	else if (c == 'u')
		return (ft_hexa(va_arg(ap, unsigned int), "0123456789abcdef", 10));
	else if (c == 'p')
	{
		p = va_arg(ap, unsigned long long);
		if (!p)
			return (write(1, "(nil)", 5));
		else
			return (write(1, "0x", 2) + ft_hexa(p, "0123456789abcdef", 16));
	}
	else if (c == '%')
		return (write(1, "%%", 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		n;
	va_list	ap;

	n = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%' && str++)
			n += ft_conditions(*str++, ap);
		else
			n += write(1, str++, 1);
	}
	va_end(ap);
	return (n);
}
