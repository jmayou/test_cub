/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:38:53 by jmayou            #+#    #+#             */
/*   Updated: 2025/05/08 11:49:06 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <mlx.h>
# include "../parsing/header.h"
#define PLAYER_SIZE 1
#define BLOCK_SIZE 20

# define WIDTH 2000
# define HEIGHT 2000
# define PLAYER_SPEED 1

# define A 0
# define S 1
# define D 2
# define W 13
# define LEFT 123
# define RIGHT 124
# define texture_width 64;
# define texture_height 64;

// # define A 100
// # define S 119
// # define D 97
// # define W 115
// # define LEFT 65363
// # define RIGHT 65361
typedef struct s_player
{
    float   x;
    float   y;
    float   angle;

    bool    key_d;
    bool    key_w;
    bool    key_a;
    bool    key_s;
    bool    key_left;
    bool    key_right;
    
}t_player;

typedef struct s_mlx
{
    void *mlx;
    void *win;
    void *img;
    
    char		*addr;      // add for awel pixel 
	int			bits_per_pixel;     // xhal kayhtaj kol pixel mn bit
	int			line_length;      // xhal kayhtaj kol star Y mn bit
	int			endian;      // tarika d takhzin
    char    **map;
    t_player    player;
    //
    char *no_texture_path;
    char *so_texture_path;
    char *we_texture_path;
    char *ea_texture_path;
    unsigned int *no_texture;
    unsigned int *so_texture;
    unsigned int *we_texture;
    unsigned int *ea_texture;
    //
    int    map_width;
    int    map_height;
    t_data *data;
} t_mlx;

void    init_player(t_mlx *mlx);
int	    close_window(t_mlx *mlx);
int    keyboard_on(int key,void *mlx);
int    keyboard_off(int key,void *playe);
void    move_player(t_player *player,t_mlx *mlx);
bool    it_s_a_wall(float px,float py,t_mlx *mlx);
void    init(t_mlx *mlx,t_data *data);
void    put_pixel(int x,int y,t_mlx *mlx,int color);
void    draw_square(int x, int y,int size,int color,t_mlx *mlx);
void    clean_image(t_mlx *mlx);
void    draw_map(t_mlx *mlx);
float   get_distance(float px,float py,float rx,float ry);
void    draw_angle_view(t_mlx  *mlx,float   start_ray,int i);
int   check_update(void *ml);
char    **mapp(t_mlx *mlx, t_data *data);
int     map_height(char **map);
int     map_width(char **map);


#endif
