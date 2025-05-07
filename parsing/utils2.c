/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-aziz <fel-aziz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 11:35:27 by fel-aziz          #+#    #+#             */
/*   Updated: 2025/05/05 08:56:33 by fel-aziz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"



/*while (data->ident != NULL)
{
	if (data->ident->identifier)
		printf("identi--> %s\n", data->ident->identifier);
	if (data->ident->arg_C)
		printf("rgb -> [%d] [%d] [%d]\n", data->ident->arg_C[0], data->ident->arg_C[1], data->ident->arg_C[2]);
	if (data->ident->arg_F)
		printf("rgb -> [%d] [%d] [%d]\n", data->ident->arg_F[0], data->ident->arg_F[1], data->ident->arg_F[2]);
	if (data->ident->path)
		printf("Path: %s\n", data->ident->path);
	printf("-----------------------------------------------------------------\n");
	data->ident = data->ident->next;
}*/


t_identifiers	*ft_new_node(char *i, char *p, int *C,int *F)
{
	t_identifiers	*newnode;

	newnode = malloc(sizeof(t_identifiers));
	if (newnode == NULL)
		return (NULL);
	newnode->identifier = i;
	newnode->path = p;
	newnode->arg_C = C;
	newnode->arg_F = F;
	newnode->next = NULL;
	return (newnode);
}

void	add_at_back(t_identifiers **head, t_identifiers *newnode)
{
	if (newnode != NULL)
	{
		if (*head == NULL)
			*head = newnode;
		else
		{
			t_identifiers *tmp = *head;
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = newnode;
		}
	}
}


int	check_is_number(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 0;
	if (( str[i] == '+') && (str[i + 1] != '\0'))
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		i++;
	if (i == len)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}


// void	handle_error_and_exit(char *tokens)
// {
// 	write(2, "Error\n", 6);
// 	// free(tokens);
// 	exit(1);
// }

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	r;
	long	result;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	r = result * sign;
	if (r < -2147483648 || r > 2147483647)
	{
		return(300);
		exit(1);
		// free
	}
		// handle_error_and_exit(tokens);
	return ((int)(r));
}