/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 08:57:41 by fel-aziz          #+#    #+#             */
/*   Updated: 2025/05/08 19:16:07 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void free_double_array(char **str)
{
	int i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void process_element(t_data *data)
{
	char	*line;
	char **str; 
	int count = 0;
	//  if a element not found 
	line = get_next_line(data->cub_fd);  
	while (line != NULL)
	{
		convert_tabs_to_spaces(line);
		if(check_is_empty(line) == 1 )
		{
			 count++;
			
			str = ft_split(line, ' ');
			if(  (ft_len(str) == 3 && ft_strncmp("\n",str[2],1) == 0 ) || ft_len(str) == 2)
			{
				is_identifier_valid(str, data);
			}
			else
			{
				ft_printf("error\nthe line < %s > contain mor than or not 2 string\n",line); 
				exit(1);
			}
			// free_double_array(str);
		}
		if(count == 6 )
		{	
			break;
		}
		free(line);
		line = get_next_line(data->cub_fd);
	}
	free(line);
}
void init_data(t_data **data )
{
	
	*data = malloc(sizeof(t_data));
	if(*data == NULL)
		return;
	(*data)->cub_fd = -99;
	(*data)->no_set = false;
    (*data)->so_set = false;
    (*data)->we_set = false;
    (*data)->ea_set = false;
    (*data)->f_set = false;
    (*data)->c_set = false;
	(*data)->ident = NULL;

	// (*data)->N_set = 0;
	// (*data)->S_set = 0;
	// (*data)->E_set = 0;
	// (*data)->W_set = 0;

	(*data)->ma = NULL;
}

void convert_tabs_to_spaces(char *line)
{
	int i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
}

void is_identifier_valid(char **line , t_data *data)
{
	
	if(ft_strncmp(line[0],"NO",ft_strlen(line[0])) == 0 && valid_NO(line,data) == 0)
	{
		add_at_back(&data->ident, ft_new_node(line[0],line[1],NULL,NULL));
	}
	else if((ft_strncmp(line[0],"SO",ft_strlen(line[0])) == 0) && valid_SO(line,data) == 0)
	{
		add_at_back(&data->ident, ft_new_node(line[0],line[1],NULL,NULL));
	}
	else if((ft_strncmp(line[0],"WE",ft_strlen(line[0])) == 0) && valid_WE(line,data) == 0)
	{
		add_at_back(&data->ident, ft_new_node(line[0],line[1],NULL,NULL));
	}
	else if((ft_strncmp(line[0],"EA",ft_strlen(line[0])) == 0) && valid_EA(line,data) == 0)
	{
		add_at_back(&data->ident, ft_new_node(line[0],line[1],NULL,NULL));
	}
	else if(ft_strncmp(line[0],"F",ft_strlen(line[0])) == 0 && valid_F(line,data) == 0)
	{
	}
	else if(ft_strncmp(line[0],"C",ft_strlen(line[0])) == 0 && valid_C(line, data) == 0)
	{
		

	}
	else
	{
		
		exit(9);
		// free;
		// exit
	}
	// printf("identifier = %s\n",line[0]);
	// for(int i = 0; line[i]; i++)
	// {
	// 	printf("line[%d] = %s\n",i,line[i]);
	// }
	// printf ("----------------------------------\n");
}

int valid_C(char **line,t_data *data)
{
	
	int *s;
	char *tmp;
	if(data->c_set == true)
	{
		ft_printf("error\nthe line is duplicate\n");
		return(1);
	}
	char **rgb = ft_split(line[1],',');
	if(ft_len(rgb) != 3)
	{
		ft_printf("error\nthe rgb not have 3 element\n");
		return(1);
	}
	tmp = ft_strtrim(rgb[2],"\n");
	if(check_is_number(rgb[0]) == 0 || check_is_number(rgb[1]) == 0 || check_is_number(tmp) == 0)
	{
		free(tmp);
		ft_printf("error\nthe rgb is not a number or negative\n");
		return(1);
	}
	free(tmp);
	if(ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[2]) > 255)
	{
		ft_printf("error\n the number must be range  0 to 255\n");
		return(1);
	}
	s = ft_convert(rgb);
	add_at_back(&data->ident, ft_new_node(line[0],NULL,s,NULL));
	free_double_array(rgb);
	data->c_set = true;
	return(0);
}

int valid_F(char **line,t_data *data)
{
	
	int *s;
	char *tmp;
	if(data->f_set == true)
	{
		ft_printf("error\nthe line is duplicate\n");
		return(1);
	}
	char **rgb = ft_split(line[1],',');
	if(ft_len(rgb) != 3)
	{
		ft_printf("error\nthe rgb not have 3 element\n");
		return(1);
	}
	tmp = ft_strtrim(rgb[2],"\n");
	if(check_is_number(rgb[0]) == 0 || check_is_number(rgb[1]) == 0 || check_is_number(tmp) == 0)
	{
		free(tmp);
		ft_printf("error\nthe rgb is not a number or negative\n");
		return(1);
	}
	free(tmp);
	if(ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[2]) > 255)
	{
		ft_printf("error\n the number must be range  0 to 255\n");
		return(1);
	}
	s = ft_convert(rgb);
	add_at_back(&data->ident, ft_new_node(line[0],NULL,NULL,s));
	t_identifiers *loop = data->ident;
	while (loop)
	{
		if(loop->arg_F == s)
		{
			data->ident->arg_F = s;
			break;
		}
		loop = loop->next;
	}
	free_double_array(rgb);
	data->f_set = true;
	return(0);
}

int *ft_convert(char **rgb)
{
	int *p;
	p = malloc(sizeof(int) * 3);
	if(p == NULL)
		return(NULL);
	p[0] = ft_atoi(rgb[0]);
	p[1] = ft_atoi(rgb[1]);
	p[2] = ft_atoi(rgb[2]);
	return(p); 
}

int valid_EA(char **line,t_data *data)
{
	char *tmp;
	if(data->ea_set == true)
	{
		ft_printf("error\nthe line is duplicate\n");
		return(1);
	}
	tmp = ft_strtrim(line[1],"\n");
	// data->texture_fd = open(tmp,O_RDONLY);
	// if(data->texture_fd < 0)
	// {
	// 	ft_printf("error\nthe path of the textue is invalide\n");
	// 	return(1);
	// }
	// close(data->texture_fd);
	free(tmp);
	data->ea_set = true;
	return(0);	
}

int valid_WE(char **line,t_data *data)
{
	if(data->we_set == true)
	{
		ft_printf("error\nthe line is duplicate\n");
		return(1);
	}
	char *tmp;
	tmp = ft_strtrim(line[1],"\n");
	// data->texture_fd = open(tmp,O_RDONLY);
	// if(data->texture_fd < 0)
	// {
	// 	ft_printf("error\nthe path of the textue is invalide\n");
	
	// 	return(1);
	// }
	// close(data->texture_fd);
	free(tmp);
	data->we_set = true;
	return(0);	
}
int valid_SO(char **line,t_data *data)
{
	if(data->so_set == true)
	{
		ft_printf("error\nthe line is duplicate\n");
		return(1);
	}
	char *tmp;
	tmp = ft_strtrim(line[1],"\n");
	// data->texture_fd = open(tmp,O_RDONLY);
	// if(data->texture_fd < 0)
	// {
	// 	ft_printf("error\nthe path of the textue is invalide\n");
	
	// 	return(1);
	// }
	// close(data->texture_fd);
	free(tmp);
	data->so_set = true;
	return(0);	
}



void	check_file_extension(char *av)
{
	int	len;

	len = ft_strlen(av);
	if (len < 5 || ft_strncmp(av + len - 4, ".cub", 4) != 0)
	{
		ft_printf("Error\nThe file must end with .cub\n");
		exit(1);
	}
}
int valid_NO(char **line,t_data *data)
{
	if(data->no_set == true)
	{
		ft_printf("error\nthe line is duplicate\n");
		return(1);
	}
	char *tmp;
	tmp = ft_strtrim(line[1],"\n");
	// data->texture_fd = open(tmp,O_RDONLY);
	// if(data->texture_fd < 0)
	// {
	// 	ft_printf("error\nthe path of the textue is invalide\n");
	// 	// close(data->texture_fd);
	// 	// free;
	// 	return(1);
	// }
	close(data->texture_fd);
	free(tmp);
	data->no_set = true;
	return(0);
}