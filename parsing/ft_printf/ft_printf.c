/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:05:33 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/03/15 10:22:17 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_checktype(char c, va_list ptr, int *len)
{
	if (c == 'c')
		ft_putchar(va_arg(ptr, int), len);
	else if (c == 's')
		ft_putstr(va_arg(ptr, char *), len);
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(ptr, int), len);
	else if (c == 'x')
		ft_putlower_hexa(va_arg(ptr, unsigned int), len);
	else if (c == 'X')
		ft_putopper_hexa(va_arg(ptr, unsigned int), len);
	else if (c == 'u')
		ft_unsnbr(va_arg(ptr, int), len);
	else if (c == 'p')
		ft_put_adrs(va_arg(ptr, unsigned long), len);
	else if (c == '%')
		ft_putchar('%', len);
	else
		ft_putchar(c, len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	ptr;

	va_start(ptr, str);
	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			ft_checktype(str[i + 1], ptr, &len);
			i++;
		}
		else if (str[i] != '%')
		{
			ft_putchar(str[i], &len);
		}
		i++;
	}
	va_end(ptr);
	return (len);
}
