/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:37:58 by jmayou            #+#    #+#             */
/*   Updated: 2025/05/05 10:57:12 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


void    init(t_mlx *mlx)
{
    mlx->mlx = mlx_init();
    mlx->win = mlx_new_window(mlx->mlx,WIDTH,HEIGHT,"cub3d");
    mlx->img = mlx_new_image(mlx->mlx,WIDTH,HEIGHT);
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);

}
void    put_pixel(int x,int y,t_mlx *mlx,int color)
{
    char *dst;
    if(y >= HEIGHT || x >= WIDTH || x < 0 || y < 0)
        return;
    dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}
void    draw_square(int x, int y,int size,int color,t_mlx *mlx)
{
    int i = 0;
    while(i <= size )
    {
        put_pixel(x + i,y,mlx,color);
        i++;
    }
    i = 0;
    while(i <= size )
    {
        put_pixel(x  + size ,y + i,mlx,color);
        i++;
    }
    i = 0;
    while(i <= size )
    {
        put_pixel(x  + i ,y + size,mlx,color);
        i++;
    }
    i = 0;
    while(i <= size )
    {
        put_pixel(x ,y + i,mlx,color);
        i++;
    }
}

void    clean_image(t_mlx *mlx)
{
    int i ;
    int j ;

    i = 0;
    j = 0;
    while(i < WIDTH)
    {
        j = 0;
        while(j < HEIGHT)
        {
            put_pixel(i,j,mlx,0x000000);
            j++;
        }
        i++;
    }
}
void    draw_map(t_mlx *mlx)
{
    char **mp = mlx->map;
    int i = 0;
    int j = 0;
    while(mp[i])
    {
        j = 0;
        while(mp[i][j])
        {
            if(mp[i][j] == '1')
                draw_square(j * BLOCK_SIZE,i * BLOCK_SIZE,BLOCK_SIZE,0x0000F0,mlx);
            j++;
        }
        i++;
    }
}
bool    it_s_a_wall(float px,float py,t_mlx *mlx)
{
    int x = px / BLOCK_SIZE;
    int y = py / BLOCK_SIZE;

    if(mlx->map[y][x] == '1')
        return(true);
    else 
        return(false);
}

int   check_update(void *ml)
{
    t_mlx *mlx = (t_mlx *)ml;
    float cos_angle;
    float sin_angle;
    float ray_x;
    float ray_y;
    move_player(&mlx->player);
    clean_image(mlx);
    draw_map(mlx);
    draw_square(mlx->player.x,mlx->player.y,20,0xFF0000,mlx);
    ray_x = mlx->player.x;
    ray_y = mlx->player.y;
    cos_angle = cos(mlx->player.angle);
    sin_angle = sin(mlx->player.angle);
    while(it_s_a_wall(ray_x,ray_y,mlx) != true)
    {
        put_pixel(ray_x,ray_y,mlx,0xFF0000);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }    
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
    return(0);
}

char **mapp(void)
{
    char **map = malloc(sizeof(char *) * 11 + 1);
    map[0] = "111111111111111";
    map[1] = "100000000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000001";
    map[4] = "100000000000001";
    map[5] = "100000010000001";
    map[6] = "100001000000001";
    map[7] = "100000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}
int main()
{
    t_mlx mlx;
    init(&mlx);
    init_player(&mlx.player);
    mlx.map = mapp();

    
    mlx_hook(mlx.win,2,1L<<0,keyboard_on,&mlx.player);
    mlx_hook(mlx.win, 3, 1L<<1, keyboard_off, &mlx.player);
    mlx_loop_hook(mlx.mlx,check_update,&mlx);

    mlx_loop(&mlx);
}