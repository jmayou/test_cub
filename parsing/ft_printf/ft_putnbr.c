/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:55:51 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/02/25 15:59:47 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int nb, int *len)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*len) += 11;
		return ;
	}
	if (nb < 0)
	{
		nb = nb * -1;
		ft_putchar('-', len);
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10, len);
		ft_putnbr(nb % 10, len);
	}
	else
	{
		ft_putchar(nb + 48, len);
	}
}
