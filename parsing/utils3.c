/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   	                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:33:51 by fel-aziz          #+#    #+#             */
/*   Updated: 2025/05/05 09:41:51 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


int has_double_player(const char *line)
{
    int j = 0;
    int count = 0;
    while (line[j])
    {
        if (line[j] == 'N' || line[j] == 'S' ||
            line[j] == 'E' || line[j] == 'W')
            count++;
        j++;
    }
    return count; // return how many player chars were found
}



int invalid_char( char *line)
{
    int i = 0;
    while (line[i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
        {
            return 1; 
        }
        i++;
    }
    return 0; 
}

int is_map_only_walls(char **maps, int n)
{
    int i = 0;
    while (i < n) {
        int j = 0;
        while (maps[i][j] != '\0') 
        {
            if (maps[i][j] != '1') 
            {
                return 0; 
            }
            j++;
        }
        i++;
    }
    return 1;
}



int	is_invalid_surrounding(char **map, int i, int j)
{
	if (map[i][j] == '0' || map[i][j] == 'N' ||
		map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
	{
		// Check top
		if (i == 0 || map[i - 1][j] == ' ')
			return (1);
		// Check bottom
		if (map[i + 1] == NULL || j >= (int)ft_strlen(map[i + 1]) || map[i + 1][j] == ' ')
			return (1);
		// Check left
		if (j == 0 || map[i][j - 1] == ' ')
			return (1);
		// Check right
		if (map[i][j + 1] == '\0' || map[i][j + 1] == ' ')
			return (1);
	}
	return (0);
}

int	check_spaces_near_open_tiles(char **map)
{
	int	i = 0;
	int	j;
	if(map == NULL)
		return(0);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_invalid_surrounding(map, i, j))
			{
				ft_printf("Error\ntile at (%d,%d) is next to a space\n", i, j);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}


