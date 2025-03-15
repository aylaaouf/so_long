/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 04:18:25 by aylaaouf          #+#    #+#             */
/*   Updated: 2024/11/14 17:57:39 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	i;
	int	count;

	if (!str)
		return (ft_putstr("(null)"));
	i = 0;
	count = 0;
	while (str[i])
	{
		count += write(1, &str[i], 1);
		i++;
	}
	return (count);
}

int	ft_puthex(unsigned long n, int cases)
{
	char	*hex;
	int		count;

	count = 0;
	if (cases == 0)
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (n >= 16)
		count += ft_puthex(n / 16, cases);
	count += ft_putchar(hex[n % 16]);
	return (count);
}

int	ft_putptr(void *ptr)
{
	int	count;

	count = 0;
	count += ft_putstr("0x");
	count += ft_puthex((unsigned long)ptr, 0);
	return (count);
}

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		return (ft_putstr("-2147483648"));
	}
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n < 10)
	{
		count += ft_putchar(n + '0');
	}
	else
	{
		count += ft_putnbr(n / 10);
		count += ft_putchar((n % 10) + '0');
	}
	return (count);
}

int	ft_putunsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n < 10)
	{
		count += ft_putchar(n + '0');
	}
	else
	{
		count += ft_putunsigned(n / 10);
		count += ft_putchar((n % 10) + '0');
	}
	return (count);
}
