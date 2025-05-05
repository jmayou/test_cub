/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:37:58 by jmayou            #+#    #+#             */
/*   Updated: 2025/05/05 15:04:26 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


void    init(t_mlx *mlx)
{
    mlx->mlx = mlx_init();
    mlx->win = mlx_new_window(mlx->mlx,WIDTH,HEIGHT,"cub3d");
    mlx->img = mlx_new_image(mlx->mlx,WIDTH,HEIGHT);
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
    mlx->map_width = 0;
    mlx->map_height = 0;
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

    // bax ma nfotoxi tol w l3ard
    if (x < 0 || x >= mlx->map_width || y < 0 || y >= mlx->map_height)
        return true;

    if(mlx->map[y][x] == '1')
        return(true);
    else 
        return(false);
}
float   get_distance(float px,float py,float rx,float ry)
{
    float d = 0;
    float dilta_x = (rx - px) * (rx - px);
    float dilta_y = (ry - py) * (ry - py);
    d = sqrt(dilta_x + dilta_y);
    return(d);
}
void    draw_angle_view(t_mlx  *mlx,float   start_ray,int i)
{
    float cos_angle;
    float sin_angle;
    float ray_x;
    float ray_y;
    ray_x = mlx->player.x;
    ray_y = mlx->player.y;
    cos_angle = cos(start_ray);
    sin_angle = sin(start_ray);
    while(it_s_a_wall(ray_x,ray_y,mlx ) != true)
    {
        put_pixel((int)ray_x, (int)ray_y,mlx,0xFF0000);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
    float d = get_distance(mlx->player.x,mlx->player.y,ray_x,ray_y) * cos(start_ray - mlx->player.angle);
    float h = (BLOCK_SIZE / d) * (WIDTH / 2);
    int start_wall = (HEIGHT - h) / 2;
    int end_wall = start_wall + h;
    while(start_wall < end_wall)
    {
        put_pixel(i,start_wall,mlx,0x0000F0);
        start_wall++;
    }
}
int   check_update(void *ml)
{
    t_mlx *mlx = (t_mlx *)ml;
    float   angle_b_two_rays = M_PI / 3 / WIDTH;
    float   start_ray = mlx->player.angle - (M_PI / 6);
    int i = 0;
    move_player(&mlx->player,mlx);
    clean_image(mlx);
    draw_map(mlx);
    draw_square(mlx->player.x,mlx->player.y,10,0xFF0000,mlx);
    while(i < WIDTH)
    {
        draw_angle_view(mlx,start_ray,i);
        start_ray += angle_b_two_rays;
        i++;
    }
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
    return(0);
}

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
                mlx->player.x = x * BLOCK_SIZE + BLOCK_SIZE / 2;
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

char **mapp(t_mlx *mlx)
{
    char **map = malloc(sizeof(char *) * (11 + 1));
    map[0] = strdup("111111111111111");
    map[1] = strdup("100000000000001");
    map[2] = strdup("100000000000001");
    map[3] = strdup("100000010000001");
    map[4] = strdup("10000N000000001");
    map[5] = strdup("100000000000001");
    map[6] = strdup("100010000000001");
    map[7] = strdup("100000000010001");
    map[8] = strdup("100000000000001");
    map[9] = strdup("111111111111111");
    map[10] = NULL;
    // hayd mni strlen
    int i = 0;
    int max_len = 0;
    while (map[i])
    {
        max_len = strlen(map[i]);
        if(max_len > mlx->map_width)
            mlx->map_width = max_len;
        i++;
    }
    mlx->map_height = i;
    return (map);
}
int main()
{
    t_mlx mlx;
    init(&mlx);
    init_player(&mlx.player);
    mlx.map = mapp(&mlx);
    set_player_start_from_map(&mlx);
    
    mlx_hook(mlx.win,2,1L<<0,keyboard_on,&mlx.player);
    mlx_hook(mlx.win, 3, 1L<<1, keyboard_off, &mlx.player);
    mlx_loop_hook(mlx.mlx,check_update,&mlx);

    mlx_loop(mlx.mlx);
    // mlx_loop(&mlx); // ma khdmlix f linux
}