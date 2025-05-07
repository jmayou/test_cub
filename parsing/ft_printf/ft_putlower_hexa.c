/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlower_hexa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:51:12 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/02/24 20:31:45 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_remlace(unsigned int nb, int *len)
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

void	ft_putlower_hexa(unsigned int nb, int *len)
{
	if (nb >= 16)
	{
		ft_putlower_hexa(nb / 16, len);
		ft_putlower_hexa(nb % 16, len);
	}
	if (nb < 10)
	{
		ft_putchar(nb + 48, len);
	}
	else
	{
		ft_remlace(nb, len);
	}
}
