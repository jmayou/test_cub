/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:14:17 by fel-aziz          #+#    #+#             */
/*   Updated: 2025/05/06 16:37:24 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char **add_line_to_map(char **maps, char *line, int n)
{
	char **tmp = malloc(sizeof(char *) * (n + 2));
	if (!tmp)
		exit(1);
	int i = 0;
	while (maps && maps[i])
	{
		tmp[i] = maps[i];
		i++;
	}
	// for (int i = 0; i < n; i++)
	// 	tmp[i] = maps[i];
	tmp[n] = line;
	tmp[n + 1] = NULL;
	free(maps);
	return tmp;
}
void ft_print_map(char **map)
{
	int i = 0;
	if (!map)
		return;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	printf("----------------------------\n");

}


void process_map(t_data *data)
{
	char *line;
	int player = 0;
	char **maps = NULL;
	int n = 0;
	char *tmp;

	line = get_next_line(data->cub_fd);
	while(line != NULL)
	{
		convert_tabs_to_spaces(line);
		tmp = ft_strtrim(line,"\n");
		free(line);
		line = ft_strdup(tmp);
		free(tmp);
		if(check_is_empty(line) == 0 )
		{
			ft_printf("the line is empty \n");
			player++;
			// break;
			exit(9);
		}
		else if(invalid_char(line) == 1)
		{
			player++;
			ft_printf("erorr\nMap contains invalid characters or double player\n");
			// break;
			exit(9);
		}

		int count = has_double_player(line);
		if (count > 0)
		{
    		player += count;
    		if (player > 1)
    		{
       	 		ft_printf("Error\nThe player is double\n");
				exit(9);
    		}
		}
		tmp = ft_strtrim(line,"\n");
		if(n == 0)
			maps = add_line_to_map(maps, ft_strtrim(data->first_line, "\n"),n);
		maps = add_line_to_map(maps, tmp, n + 1);
		free(line);
		// free(tmp);
		line = get_next_line(data->cub_fd);
		n++;
	}
	free(line);
	if (player == 0)
	{
		ft_printf("Error\nNo player found in the map\n");
		exit(1);
	}
	if(is_map_only_walls(maps, n) == 1)
	{
		ft_printf("error\n Map contains only walls, no playable area or player position\n");
		exit(9);
	}
	data->ma = maps;
}
void skip_empty_line(t_data *data)
{
	char *line;
	line = get_next_line(data->cub_fd);
	while(line != NULL && check_is_empty(line) == 0)
	{
		free(line);
		line = get_next_line(data->cub_fd);
	}
	data->first_line = line;
}

int check_element(t_data *data)
{

	if(data->no_set == false || data->so_set == false || data->we_set == false || data->ea_set == false || data->f_set == false  || data->c_set == false ) 
	{
		return(1);
	}
	return(0);
}

void parsing(t_data *data , int ac ,char *av[])
{
	if (ac != 2)
	{
		ft_printf("Error\nThis program accepts exactly two arguments.\n");
		exit(1);
	}
	check_file_extension(av[1] );
	data->cub_fd = open(av[1], O_RDONLY);
	if (data->cub_fd < 0)
	{
		perror("error\n");
		exit(9);
	}
	process_element(data);
	if(check_element(data) == 1)
	{
		ft_printf("error\n one fo elemet not exist \n");
		exit(9);
	}
	skip_empty_line(data);
	process_map(data);
	// ft_print_map(data->ma);
	if (check_spaces_near_open_tiles(data->ma) == 1)
		exit(1);
}
// int	main(int ac, char *av[])
// {
	
// 	t_data *data = NULL;
// 	init_data(&data);
// 	if(data == NULL)
// 		exit(1);
// 	parsing(data ,ac ,av);
	
// 	return (0);
// }

