/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putopper_hexa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:45:44 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/02/24 20:32:00 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_remlace(unsigned int nb, int *len)
{
	if (nb == 10)
		ft_putchar('A', len);
	if (nb == 11)
		ft_putchar('B', len);
	if (nb == 12)
		ft_putchar('C', len);
	if (nb == 13)
		ft_putchar('D', len);
	if (nb == 14)
		ft_putchar('E', len);
	if (nb == 15)
		ft_putchar('F', len);
}

void	ft_putopper_hexa(unsigned int nb, int *len)
{
	if (nb >= 16)
	{
		ft_putopper_hexa(nb / 16, len);
		ft_putopper_hexa(nb % 16, len);
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
