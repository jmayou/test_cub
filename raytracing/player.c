/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:17:12 by jmayou            #+#    #+#             */
/*   Updated: 2025/05/06 17:20:27 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void set_player_start_from_map(t_mlx *mlx)
{
    int y = 0;
    while (mlx->map[y])
    {
        int x = 0;
        while (mlx->map[y][x])
        {
            char c = mlx->map[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                mlx->player.x = x * BLOCK_SIZE + BLOCK_SIZE / 2; // * for trnsf from map to pexil + for player ykon f wsat bock
                mlx->player.y = y * BLOCK_SIZE + BLOCK_SIZE / 2;
                if (c == 'N')
                    mlx->player.angle = 3 * M_PI / 2; // fo9
                else if (c == 'S')
                    mlx->player.angle = M_PI / 2;     // taht
                else if (c == 'E')
                    mlx->player.angle = 0;           // limn
                else if (c == 'W')
                    mlx->player.angle = M_PI;        // lisr
                mlx->map[y][x] = '0'; // bax nrj3oha 3adia
                return;
            }
            x++;
        }
        y++;
    }
}
void    init_player(t_mlx *mlx)
{
    set_player_start_from_map(mlx);
    mlx->player.key_left = false;
    mlx->player.key_right = false;
    
    mlx->player.key_a = false;
    mlx->player.key_w = false;
    mlx->player.key_d = false;
    mlx->player.key_s = false;
}

int	close_window(t_mlx *mlx)
{
	exit(0);
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	return (0);
}

int    keyboard_on(int key,void *ml)
{
    t_mlx *mlx = (t_mlx *)ml;
    if(key == A)
        mlx->player.key_a = true;
    if(key == W)
        mlx->player.key_w = true;
    if(key == D)
        mlx->player.key_d = true;
    if(key == S)
        mlx->player.key_s = true;
    if(key == LEFT)
        mlx->player.key_left = true;
    if(key == RIGHT)
        mlx->player.key_right = true; 
    if(key == 53 || key == 17)
        close_window(mlx);
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