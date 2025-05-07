/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:59:27 by fel-aziz          #+#    #+#             */
/*   Updated: 2024/04/18 18:35:23 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_aftrline(char *str)
{
	int		j;
	int		i;
	char	*p;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if ((str[i] == '\0') || (str[i] == '\n' && str[i + 1] == '\0'))
		return (NULL);
	i++;
	j = i;
	while (str[i] != '\0')
		i++;
	p = malloc(i - j * sizeof(char) + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (str[j] != '\0')
	{
		p[i] = str[j];
		j++;
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_bfrline(char *str)
{
	int		i;
	char	*p;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		i++;
	}
	if (str[i] == '\0')
		return (ft_strdup(str));
	p = malloc(sizeof(char) * i + 2);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\n')
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\n';
	p[i + 1] = '\0';
	return (p);
}

int	check_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_fdread(int fd, char **aftrline)
{
	char	*red;
	ssize_t	j;
	char	*buff;

	j = 1;
	red = NULL;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (j > 0)
	{
		j = read(fd, buff, BUFFER_SIZE);
		if (j == 0)
			break ;
		if (j == -1)
		{
			free(red);
			free(*aftrline);
			*aftrline = NULL;
			return (free(buff), NULL);
		}
		buff[j] = '\0';
		red = ft_strjoin(red, buff);
		if (check_line(red) == 1)
			break ;
	}
	return (free(buff), red);
}

char	*get_next_line(int fd)
{
	char		*str;
	char		*bfrline;
	char		*red;
	static char	*aftrline;

	str = NULL;
	bfrline = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	red = ft_fdread(fd, &aftrline);
	str = ft_strjoin(aftrline, red);
	free(red);
	if (str == NULL)
		return (NULL);
	aftrline = ft_aftrline(str);
	bfrline = ft_bfrline(str);
	free(str);
	return (bfrline);
}
