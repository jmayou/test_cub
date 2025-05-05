/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:17:12 by jmayou            #+#    #+#             */
/*   Updated: 2025/05/05 15:07:12 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    init_player(t_player *player)
{
    player->x = WIDTH / 2;
    player->y = HEIGHT / 2;
    player->angle = M_PI / 2;
    
    player->key_left = false;
    player->key_right = false;
    
    player->key_a = false;
    player->key_w = false;
    player->key_d = false;
    player->key_s = false;
}

int    keyboard_on(int key,void *playe)
{
    // printf("key: %d\n", key);
    t_player *player = (t_player *)playe;
    if(key == A)
        player->key_a = true;
    if(key == W)
        player->key_w = true;
    if(key == D)
        player->key_d = true;
    if(key == S)
        player->key_s = true;
    if(key == LEFT)
        player->key_left = true;
    if(key == RIGHT)
        player->key_right = true; 
    return(0);
}

int    keyboard_off(int key,void *playe)
{
    t_player *player = (t_player *)playe;
    if(key == A)
        player->key_a = false;
    if(key == W)
        player->key_w = false;
    if(key == D)
        player->key_d = false;
    if(key == S)
        player->key_s = false;
    if(key == LEFT)
        player->key_left = false;
    if(key == RIGHT)
        player->key_right = false; 
    return(0);
}

void move_player(t_player *player,t_mlx *mlx)
{
    int move = PLAYER_SPEED;
    float angle_move = 0.03;
    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);
    float new_x = player->x;
    float new_y = player->y;

    if (player->key_left)
        player->angle -= angle_move;
    if (player->key_right)
        player->angle += angle_move;
    if (player->angle >  2 * M_PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle =  2 * M_PI;


    if (player->key_w)
    {
        new_x += cos_angle * move;
        new_y += sin_angle * move;
    }
    if (player->key_s)
    {
        new_x -= cos_angle * move;
        new_y -= sin_angle * move;
    }
    if (player->key_a)
    {
        new_x += sin_angle * move;
        new_y -= cos_angle * move;
    }
    if (player->key_d)
    {
        new_x -= sin_angle * move;
        new_y += cos_angle * move;
    }
    if(!it_s_a_wall(new_x,player->y,mlx))
        player->x = new_x;
    if(!it_s_a_wall(player->x,new_y,mlx))
        player->y = new_y;
}