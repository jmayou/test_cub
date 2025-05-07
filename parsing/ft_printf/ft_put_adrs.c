/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_adrs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:03:58 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/02/24 20:31:27 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_reemlace(unsigned long nb, int *len)
{
	if (nb == 10)
		ft_putchar('a', len);
	if (nb == 11)
		ft_putchar('b', len);
	if (nb == 12)
		ft_putchar('c', len);
	if (nb == 13)
		ft_putchar('d', len);
	if (nb == 14)
		ft_putchar('e', len);
	if (nb == 15)
		ft_putchar('f', len);
}

void	ft_puthexaa(unsigned long nb, int *len)
{
	if (nb > 15)
	{
		ft_puthexaa(nb / 16, len);
		ft_puthexaa(nb % 16, len);
	}
	if (nb < 16 && nb > 9)
	{
		ft_reemlace(nb, len);
	}
	if (nb < 10)
	{
		ft_putchar(nb + 48, len);
	}
}

void	ft_put_adrs(unsigned long nb, int *len)
{
	ft_putstr("0x", len);
	ft_puthexaa(nb, len);
}
