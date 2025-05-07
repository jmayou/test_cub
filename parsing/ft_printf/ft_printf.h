/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:59:34 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/03/15 10:14:20 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
void	ft_putchar(char c, int *len);
void	ft_putstr(char *str, int *len);
void	ft_putnbr(int nb, int *len);
void	ft_unsnbr(unsigned int nb, int *len);
void	ft_putlower_hexa(unsigned int nb, int *len);
void	ft_putopper_hexa(unsigned int nb, int *len);
void	ft_put_adrs(unsigned long nb, int *len);
#endif