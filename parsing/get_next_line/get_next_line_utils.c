/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:31:28 by fel-aziz          #+#    #+#             */
/*   Updated: 2025/05/06 18:55:33 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	lan(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *s1)
{
	int		i;
	int		len;
	char	*p;

	i = 0;
	len = lan(s1);
	p = malloc(sizeof(char) * len + 1);
	if (p == NULL)
	{
		return (NULL);
	}
	while (i < len)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	ft_copy(char *p, char *s1, char *s2)
{
	int	i;
	int	j;
	int	len1;
	int	len2;

	i = 0;
	j = 0;
	len1 = lan(s1);
	len2 = lan(s2);
	while (i < len1)
	{
		p[i] = s1[i];
		i++;
	}
	while (j < len2)
	{
		p[i] = s2[j];
		j++;
		i++;
	}
	p[i] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		len1;
	int		len2;
	char	*dup;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
	{
		return (ft_strdup(s2));
	}
	if (s2 == NULL)
	{
		dup = ft_strdup(s1);
		free(s1);
		return (dup);
	}
	len1 = lan(s1);
	len2 = lan(s2);
	p = malloc(len1 + len2 + 1);
	if (p == NULL)
		return (NULL);
	ft_copy(p, s1, s2);
	free(s1);
	return (p);
}
