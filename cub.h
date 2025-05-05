/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:38:53 by jmayou            #+#    #+#             */
/*   Updated: 2025/05/05 13:12:28 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

#include <stdio.h>
#include "mlx.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define PLAYER_SIZE 1
#define BLOCK_SIZE 20
// wind mlx
# define WIDTH 1000
# define HEIGHT 1000
# define PLAYER_SPEED 1
// keybord
// linux
// # define A 100
// # define S 119
// # define D 97
// # define W 115
// # define LEFT 65363
// # define RIGHT 65361
# define A 0
# define S 1
# define D 2
# define W 13
# define LEFT 123
# define RIGHT 124

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
    int    map_width;
    int    map_height;
} t_mlx;

void    init_player(t_player *player);
int    keyboard_on(int key,void *playe);
int    keyboard_off(int key,void *playe);
void    move_player(t_player *player,t_mlx *mlx);
bool    it_s_a_wall(float px,float py,t_mlx *mlx);


#endif