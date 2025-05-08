/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:37:58 by jmayou            #+#    #+#             */
/*   Updated: 2025/05/08 14:21:30 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "../parsing/header.h"

unsigned int *load_texture(void *mlx, char *filename, int width, int height) 
{
    void *img = mlx_xpm_file_to_image(mlx, filename, &width, &height);
    if (!img) {
        return NULL;
    }
    char *addr;
    int bits_per_pixel;
    int lne_length;
    int endian;
    addr = mlx_get_data_addr(img, &bits_per_pixel,&lne_length, &endian);
    unsigned int *texture = malloc((width) * (height) * sizeof(unsigned int));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned int color = *(unsigned int *)(addr + (y * lne_length + x * (bits_per_pixel / 8)));
            texture[y * width + x] = color;
        }
    }
    mlx_destroy_image(mlx, img);
    return texture;
}

void    init(t_mlx *mlx,t_data *data)
{
    (void)data;
    mlx->mlx = mlx_init();
    mlx->win = mlx_new_window(mlx->mlx,WIDTH,HEIGHT,"cub3d");
    mlx->img = mlx_new_image(mlx->mlx,WIDTH,HEIGHT);
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
    mlx->map_width = 0;
    mlx->map_height = 0;
    mlx->no_texture_path = strdup("./textures/test_no.xpm");
    mlx->so_texture_path = strdup("./textures/test_so.xpm");
    mlx->we_texture_path = strdup("./textures/test_we.xpm");
    mlx->ea_texture_path = strdup("./textures/test_ea.xpm");
    mlx->no_texture = load_texture(mlx,mlx->no_texture_path, 64, 64);
    mlx->so_texture = load_texture(mlx,mlx->so_texture_path, 64, 64);
    mlx->we_texture = load_texture(mlx,mlx->we_texture_path, 64, 64);
    mlx->ea_texture = load_texture(mlx,mlx->ea_texture_path, 64, 64);
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

void draw_angle_view(t_mlx *mlx, float ray_angle, int column) {
    float ray_x = mlx->player.x;
    float ray_y = mlx->player.y;
    float cos_a = cos(ray_angle);
    float sin_a = sin(ray_angle);
    float step = 0.1; 
    while (!it_s_a_wall(ray_x, ray_y, mlx)) {
        ray_x += cos_a * step;
        ray_y += sin_a * step;
    }
    float mini_step = 1.0;
    float map_ray_x = mlx->player.x;
    float map_ray_y = mlx->player.y;
    while (get_distance(map_ray_x, map_ray_y, ray_x, ray_y) > 1.0f) {
        put_pixel(map_ray_x, map_ray_y, mlx, 0xFF0000); 
        map_ray_x += cos_a * mini_step;
        map_ray_y += sin_a * mini_step;
    }
    float corrected_dist = get_distance(mlx->player.x, mlx->player.y, ray_x, ray_y) * cos(ray_angle - mlx->player.angle);
    float fov = M_PI / 3; 
    float proj_plane_dist = (WIDTH / 2.0f) / tan(fov / 2.0f);
    float wall_height = (BLOCK_SIZE * proj_plane_dist) / corrected_dist;
    int wall_start = (HEIGHT / 2) - (wall_height / 2);
    int wall_end = wall_start + wall_height;
    if (wall_start < 0) wall_start = 0;
    if (wall_end > HEIGHT) wall_end = HEIGHT;

    unsigned int *texture;
    if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2) {
        texture = mlx->no_texture;
    } else if ((ray_angle > 0 && ray_angle < M_PI / 2) || (ray_angle > 3 * M_PI / 2 && ray_angle < 2 * M_PI)) {
        texture = mlx->so_texture;
    } else if (ray_angle > M_PI && ray_angle < 3 * M_PI / 2) {
        texture = mlx->we_texture;
    } else {
        texture = mlx->ea_texture;
    }
    int y = wall_start;
    while (y < wall_end) {
        float texture_y = (y - wall_start) / wall_height * 64;
        float texture_x = (int)(ray_x / BLOCK_SIZE) % 64;
        unsigned int texture_color = texture[(int)texture_y * 64 + (int)texture_x];
    exit(1);
        put_pixel(column, y, mlx, texture_color);
        y++;
    }
}
// void draw_angle_view(t_mlx *mlx, float ray_angle, int column)
// {
//     float ray_x = mlx->player.x;
//     float ray_y = mlx->player.y;
//     float cos_a = cos(ray_angle);
//     float sin_a = sin(ray_angle);
//     float step = 0.1;

//     // Move ray forward until it hits a wall
//     while (!it_s_a_wall(ray_x, ray_y, mlx))
//     {
//         ray_x += cos_a * step;
//         ray_y += sin_a * step;
//     }

//     // rays
//     float mini_step = 1.0;
//     float map_ray_x = mlx->player.x;
//     float map_ray_y = mlx->player.y;
//     while (get_distance(map_ray_x, map_ray_y, ray_x, ray_y) > 1.0f)
//     {
//         put_pixel(map_ray_x, map_ray_y, mlx, 0xFF0000); // green mini-ray
//         map_ray_x += cos_a * mini_step;
//         map_ray_y += sin_a * mini_step;
//     }

//     // Fisheye correction
//     float corrected_dist = get_distance(mlx->player.x, mlx->player.y, ray_x, ray_y)
//                            * cos(ray_angle - mlx->player.angle);

//     // Projection plane distance (based on 60° FOV)
//     float fov = M_PI / 3; // 60 degrees
//     float proj_plane_dist = (WIDTH / 2.0f) / tan(fov / 2.0f);

//     // Calculate projected wall height
//     float wall_height = (BLOCK_SIZE * proj_plane_dist) / corrected_dist;

//     int wall_start = (HEIGHT / 2) - (wall_height / 2);
//     int wall_end = wall_start + wall_height;

//     // Clamp to screen bounds
//     if (wall_start < 0) wall_start = 0;
//     if (wall_end > HEIGHT) wall_end = HEIGHT;

//     // Draw vertical wall slice
//     // int y = wall_start;
//     // while(y < wall_end)
//     // {
//     //     put_pixel(column,y,mlx,0x0000F0);
//     //     y++;
//     // }



//         unsigned int *texture;
//     if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2) {
//         texture = mlx->no_texture;
//     } else if (ray_angle > 0 && ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2 && ray_angle < 2 * M_PI) {
//         texture = mlx->so_texture;
//     } else if (ray_angle > M_PI / 2 && ray_angle < M_PI) {
//         texture = mlx->we_texture;
//     } else {
//         texture = mlx->ea_texture;
//     }
//     int y = wall_start;
//     while (y < wall_end) {
//         float texture_y = (y - wall_start) / wall_height * texture_height;
//         float texture_x = (int)(ray_x / BLOCK_SIZE) % texture_width;
//         unsigned int texture_color = texture[(int)texture_y * texture_width + (int)texture_x];
//         put_pixel(column, y, mlx, texture_color);
//         y++;
//     }
// }

int rgb_to_int(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
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