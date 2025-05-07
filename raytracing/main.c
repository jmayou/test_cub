/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:37:58 by jmayou            #+#    #+#             */
/*   Updated: 2025/05/06 17:21:29 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "../parsing/header.h"


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

void draw_angle_view(t_mlx *mlx, float ray_angle, int column)
{
    float ray_x = mlx->player.x;
    float ray_y = mlx->player.y;
    float cos_a = cos(ray_angle);
    float sin_a = sin(ray_angle);
    float step = 0.1;

    // Move ray forward until it hits a wall
    while (!it_s_a_wall(ray_x, ray_y, mlx))
    {
        ray_x += cos_a * step;
        ray_y += sin_a * step;
    }

    // rays
    float mini_step = 1.0;
    float map_ray_x = mlx->player.x;
    float map_ray_y = mlx->player.y;
    while (get_distance(map_ray_x, map_ray_y, ray_x, ray_y) > 1.0f)
    {
        put_pixel(map_ray_x, map_ray_y, mlx, 0xFF0000); // green mini-ray
        map_ray_x += cos_a * mini_step;
        map_ray_y += sin_a * mini_step;
    }

    // Fisheye correction
    float corrected_dist = get_distance(mlx->player.x, mlx->player.y, ray_x, ray_y)
                           * cos(ray_angle - mlx->player.angle);

    // Projection plane distance (based on 60° FOV)
    float fov = M_PI / 3; // 60 degrees
    float proj_plane_dist = (WIDTH / 2.0f) / tan(fov / 2.0f);

    // Calculate projected wall height
    float wall_height = (BLOCK_SIZE * proj_plane_dist) / corrected_dist;

    int wall_start = (HEIGHT / 2) - (wall_height / 2);
    int wall_end = wall_start + wall_height;

    // Clamp to screen bounds
    if (wall_start < 0) wall_start = 0;
    if (wall_end > HEIGHT) wall_end = HEIGHT;

    // Draw vertical wall slice
    int y = wall_start;
    while(y < wall_end)
    {
        put_pixel(column,y,mlx,0x0000F0);
        y++;
    }
}

int rgb_to_int(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

void    draw_sky(t_mlx *mlx)
{
    int i = 0;
    int j = 0;

    int color = rgb_to_int(mlx->data->ident->arg_C[0],mlx->data->ident->arg_C[1],mlx->data->ident->arg_C[2]);
    while(i < WIDTH)
    {
        j = 0;
        while(j < HEIGHT / 2)
        {
            put_pixel(i,j,mlx, color);
            j++;
        }
        i++;
    }
}

void    draw_floor(t_mlx *mlx)
{
    int i = 0;
    int j = 0;
    int color = rgb_to_int(mlx->data->ident->arg_F[0],mlx->data->ident->arg_F[1],mlx->data->ident->arg_F[2]);
    while(i < WIDTH)
    {
        j = HEIGHT / 2;
        while(j < HEIGHT)
        {
            put_pixel(i,j,mlx,color);
            j++;
        }
        i++;
    }
}

int   check_update(void *ml)
{
    t_mlx *mlx = (t_mlx *)ml;
    float   angle_b_two_rays = M_PI / 3 / WIDTH;
    float   start_ray = mlx->player.angle - (M_PI / 6);
    int i = 0;
    (void)i;
    (void)start_ray;
    (void)angle_b_two_rays;
    move_player(&mlx->player,mlx);
    clean_image(mlx);
    // draw_sky(mlx);
    // draw_floor(mlx);
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

char **mapp(t_mlx *mlx, t_data *data)
{
    char **map = data->ma;
    int i = 0;
    int max_len = 0;
    while (map[i])
    {
        max_len = ft_strlen(map[i]);
        if(max_len > mlx->map_width)
            mlx->map_width = max_len;
        i++;
    }
    mlx->map_height = i;
    mlx->data = data;
    return (map);
}
// int main()
// {
//     t_mlx mlx;
//     init(&mlx);
//     mlx.map = mapp(&mlx);
//     init_player(&mlx);
    
//     mlx_hook(mlx.win,2,1L<<0,keyboard_on,&mlx);// why 2
//     mlx_hook(mlx.win, 3, 1L<<1, keyboard_off, &mlx.player); // 3
//     mlx_loop_hook(mlx.mlx,check_update,&mlx);
//     // mlx_hook(mlx.win, 53, 0, close, &mlx);
//     // mlx_hook(mlx.win, 17, 0, close, &mlx);
//     mlx_loop(mlx.mlx);
    
// }