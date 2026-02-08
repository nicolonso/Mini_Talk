/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:30:32 by nalfonso          #+#    #+#             */
/*   Updated: 2025/05/14 18:59:24 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putstrpf(char *str)
{
	int	count;

	count = 0;
	if (!str)
		str = "(null)";
	while (str[count])
	{
		write (1, &str[count], 1);
		count++;
	}
	return (count);
}

static int	ft_putbases(t_number nbr, t_number len, char *base)
{
	int	count;

	count = 1;
	if (nbr >= len)
		count += ft_putbases(nbr / len, len, base);
	write(1, &base[nbr % len], 1);
	return (count);
}

static int	ft_baseten(long nbr)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		count += write(1, "-", 1);
		nbr = -nbr;
	}
	count += ft_putbases(nbr, 10, HEXADECIMAL);
	return (count);
}

static int	ft_format(va_list args, char *format)
{
	t_number	c;

	if (*format == 'c')
	{
		c = (va_arg(args, int));
		return (write (1, &c, 1));
	}
	if (*format == 's')
		return (ft_putstrpf(va_arg(args, char *)));
	if (*format == 'p')
	{
		c = (va_arg(args, unsigned long));
		if (!c)
			return (ft_putstrpf("(nil)"));
		return (write(1, "0x", 2) + ft_putbases(c, 16, HEXADECIMAL));
	}
	if (*format == 'd' || *format == 'i')
		return (ft_baseten(va_arg(args, int)));
	if (*format == 'u')
		return (ft_baseten(va_arg(args, unsigned int)));
	if (*format == 'x')
		return (ft_putbases(va_arg(args, unsigned int), 16, HEXADECIMAL));
	if (*format == 'X')
		return (ft_putbases(va_arg(args, unsigned int), 16, CHEXADECIMAL));
	return (ft_putstrpf("%"));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int	count;

	count = 0;
	if (!format)
		return (-1);
	va_start (args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += ft_format(args, (char *) format);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(args);
	if (count < 0)
		return (-1);
	return (count);
}
// int main()
// {
// 	int i = ft_printf ("%p\n",(void *) 0);
// 	int y = printf ("%p\n",(void *)0);
// 	printf("%d\n", i);
// 	printf("%d\n", y);
// 	char *str = "Dont look please";
// 	int u = ft_printf ("%s\n", str);
// 	int j = printf ("%s\n", str);
// 	int e = ft_printf (NULL);
// 	int r = printf (NULL);
// 	printf("%i\n", e);
// 	printf("%i\n", r);
// 	char s = 'i';
// 	int n = ft_printf ("%c\n", s);
// 	int q = printf ("%c\n", s);
// 	printf("%i\n", n);
// 	printf("%i\n", q);
// 	unsigned int unsigned_number = 4294967295;
//     int l = printf("Unsigned number: %u\n", unsigned_number);
// 	int o = ft_printf("Unsigned number: %u\n", unsigned_number);
// 	printf("%d\n", l);
// 	printf("%d\n", o);
//     unsigned int hex_number = 305419896;
//     int p = ft_printf("Hexadecimal (lowercase): %x\n", hex_number);
// 	int k = printf("Hexadecimal (lowercase): %x\n", hex_number);
// 	printf("%d\n", p);
// 	printf("%d\n", k);
//     int w = ft_printf("Hexadecimal (uppercase): %X\n", hex_number);
// 	int z = printf("Hexadecimal (uppercase): %X\n", hex_number);
// 	printf("%d\n", w);
// 	printf("%d\n", z);
// 	int int_var = 42;
//     int *pointer_var = &int_var;
//     int t = printf("Pointer address: %p\n", (void *)pointer_var);
// 	int d = printf("Pointer address: %p\n", (void *) 42);
// 	int h = ft_printf("Pointer address: %p\n", (void *)pointer_var);
// 	int g = ft_printf("Pointer address: %p\n",(void *) 42);
// 	printf("%i %i %i %i\n", t, d, h,g);
// 	return (0);
// }
