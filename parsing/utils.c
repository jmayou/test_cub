/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:08:53 by fel-aziz          #+#    #+#             */
/*   Updated: 2025/05/04 09:51:23 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_strlen( char *str)
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
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] && s2[i]
		&& (unsigned char)s1[i] == (unsigned char)s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int check_is_empty(char *str)
{
	int i;
    int count;

    count = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
            count++;
        i++;
    }
    if (ft_strlen(str) == count)
        return (0);

    return (1);
}

static int	checkword(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			count++;
		}
		i++;
	}
	return (count);
}

static void	*free_mem(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	char	*p1;
	size_t	i;

	p1 = s;
	i = 0;
	while (i < n)
	{
		p1[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	char	*p;

	total = count * size;
	p = malloc(total);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, total);
	return (p);
}

char	*ft_substr(char  *s,  int start, int len)
{
	int	i;
	char	*p;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	p = malloc((len * sizeof(char)) + 1);
	if (p == NULL)
		return (NULL);
	else
	{
		while (i < len)
		{
			p[i] = s[start];
			i++;
			start++;
		}
		p[i] = '\0';
		return (p);
	}
}


char	**ft_split(char  *s, char c)
{
	char	**result;
	int		i;
	int		j;
	int		start;

	i = 0;
	start = 0;
	j = 0;
	result = malloc(sizeof(char *) * (checkword(s, c) + 1));
	if (result == NULL)
		return (NULL);
	while (j < checkword(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		result[j] = ft_substr(s, start, i - start);
		if (result[j] == NULL)
			return (free_mem(result, j));
		j++;
	}
	result[j] = NULL;
	return (result);
}


int  ft_len(char **str)
{
	int i;
	i = 0;
	while(str[i] != NULL)
	{
		i++;
	}
	return(i);
}


static int	ft_char(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char  *s1, char  *set)
{
	char	*p;
	size_t	j;
	size_t	k;
	size_t	i;

	i = 0;
	j = ft_strlen(s1);
	k = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (ft_char(s1[i], set) == 1)
		i++;
	while (j > i && ft_char(s1[(j - 1)], set) == 1)
		j--;
	p = malloc((j - i) * sizeof(char) + 1);
	if (p == NULL)
		return (NULL);
	while (i < j)
		p[k++] = s1[i++];
	p[k] = '\0';
	return (p);
}
