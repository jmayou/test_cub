#ifndef HEADER_H
#define HEADER_H
#include "get_next_line/get_next_line.h"
#include "ft_printf/ft_printf.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>


typedef struct s_identifiers
{
	char *identifier;
	char *path;
	int *arg_C;
	int *arg_F;
	struct s_identifiers	*next;
}					t_identifiers;

typedef struct s_data
{
	t_identifiers *ident ;
	// int N_set;
	// int S_set;
	// int E_set;
	// int W_set;
	bool no_set;
    bool so_set;
    bool we_set;
    bool ea_set;
    bool f_set;
    bool c_set;
	int cub_fd;
	int texture_fd;
	char **ma;
	char *first_line ;

}t_data;

// utils_func 
int	ft_strlen(char *str);
int	ft_atoi(char *str);
void	add_at_back(t_identifiers **head, t_identifiers *newnode);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	check_is_empty(char *str);
char	**ft_split(char  *s, char c);
int  ft_len(char **str);
char	*ft_strtrim(char  *s1, char  *set);
int	check_is_number(char *str);
t_identifiers	*ft_new_node(char *i, char *p, int *C,int *F);

// parsing 

void process_element(t_data *data);
void init_data(t_data **data );
void convert_tabs_to_spaces(char *line);
void is_identifier_valid(char **line , t_data *data);
int valid_C(char **line,t_data *data);
int valid_F(char **line,t_data *data);
int *ft_convert(char **rgb);
int valid_EA(char **line,t_data *data);
int valid_WE(char **line,t_data *data);
int valid_SO(char **line,t_data *data);
void	check_file_extension(char *av);
int valid_NO(char **line,t_data *data);
int invalid_char( char *line);
int has_double_player(const char *line);
int is_map_only_walls(char **maps, int n);
int	check_spaces_near_open_tiles(char **map);
void parsing(t_data *data , int ac ,char *av[]);

#endif 