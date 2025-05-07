/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:44:15 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/02/24 20:32:11 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_unsnbr(unsigned int nb, int *len)
{
	if (nb > 9)
	{
		ft_unsnbr(nb / 10, len);
		ft_unsnbr(nb % 10, len);
	}
	if (nb < 10)
	{
		ft_putchar(nb + 48, len);
	}
}
