/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmayou <jmayou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:37:58 by jmayou            #+#    #+#             */
/*   Updated: 2025/05/08 19:21:03 by jmayou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "../parsing/header.h"

t_texture	*load_texture(const char *path, void *mlx)
{
	t_texture	*texture;
	int			bpp;
	int			size_line;
	int			endian;

	texture = malloc(sizeof(t_texture));
	if (!texture)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}

	texture->img = mlx_xpm_file_to_image(mlx, (char *)path, &texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Error: Failed to load image: %s\n", path);
		free(texture);
		exit(1);
	}

	texture->adr = (uint32_t *)mlx_get_data_addr(texture->img, &bpp, &size_line, &endian);
	return (texture);
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
    mlx->no_texture_path = strdup("./textures/gg.xpm");
    mlx->so_texture_path = strdup("./textures/test_so.xpm");
    mlx->we_texture_path = strdup("./textures/test_we.xpm");
    mlx->ea_texture_path = strdup("./textures/test_ea.xpm");
    mlx->no_texture = load_texture(mlx->no_texture_path,mlx->mlx);
    mlx->so_texture = load_texture(mlx->so_texture_path,mlx->mlx);
    mlx->we_texture = load_texture(mlx->we_texture_path,mlx->mlx);
    mlx->ea_texture = load_texture(mlx->ea_texture_path,mlx->mlx);
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
        put_pixel(x  + size ,y + i,mlx,color);
        put_pixel(x  + i ,y + size,mlx,color);
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
    if (x < 0  || x >= mlx->map_width || y < 0 || y >= mlx->map_height)
    {
        return true;
    }

    int row_len = ft_strlen(mlx->map[y]);
    if (x >= row_len || mlx->map[y][x] == ' ' || mlx->map[y][x] == '\0')
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

// Updated draw_angle_view function with improved texture rendering
void draw_angle_view(t_mlx *mlx, float ray_angle, int column)
{
    float ray_x = mlx->player.x;
    float ray_y = mlx->player.y;
    float step = 0.1;
    float cos_a = cos(ray_angle);
    float sin_a = sin(ray_angle);
    float prev_x = ray_x;
    float prev_y = ray_y;
    (void)prev_x;
    (void)prev_y;
    // Cast the ray
    while (!it_s_a_wall(ray_x, ray_y, mlx))
    {
        prev_x = ray_x;
        prev_y = ray_y;
        ray_x += cos_a * step;
        ray_y += sin_a * step;
    }

    // Calculate exact hit position for precise texture mapping
    float wall_x, wall_y;
    int map_x = (int)(ray_x / BLOCK_SIZE);
    int map_y = (int)(ray_y / BLOCK_SIZE);
    
    // Determine which side of the wall was hit
    bool hit_vertical = false;
    if (abs((int)ray_x / BLOCK_SIZE - (int)prev_x / BLOCK_SIZE) > 0)
        hit_vertical = true;
        
    // Store the exact impact position
    if (hit_vertical) {
        wall_y = ray_y;
        if (cos_a > 0) // Hit west face
            wall_x = map_x * BLOCK_SIZE;
        else // Hit east face
            wall_x = (map_x + 1) * BLOCK_SIZE;
    } else {
        wall_x = ray_x;
        if (sin_a > 0) // Hit north face
            wall_y = map_y * BLOCK_SIZE;
        else // Hit south face
            wall_y = (map_y + 1) * BLOCK_SIZE;
    }

    // Correct fish-eye effect
    float corrected_dist = get_distance(mlx->player.x, mlx->player.y, ray_x, ray_y) 
                            * cos(ray_angle - mlx->player.angle);
    if (corrected_dist < 0.1)
        corrected_dist = 0.1; // Prevent division by zero

    // Calculate wall height
    float fov = M_PI / 3;
    float proj_plane_dist = (WIDTH / 2.0f) / tan(fov / 2.0f);
    float wall_height = (BLOCK_SIZE * proj_plane_dist) / corrected_dist;

/////////////////////////////////////////////////////////

    // Draw minimap ray
    int start_x = mlx->player.x;
    int start_y = mlx->player.y;
    int end_x = ray_x;
    int end_y = ray_y;
    
    // Draw the ray line on minimap
    float dx = end_x - start_x;
    float dy = end_y - start_y;
    float steps = fmax(fabs(dx), fabs(dy));
    float x_inc = dx / steps;
    float y_inc = dy / steps;
    float x = start_x;
    float y = start_y;
    
    for (int i = 0; i <= steps; i++) {
        put_pixel(x, y, mlx, 0xFF0000); // Red color for rays
        x += x_inc;
        y += y_inc;
    }



/////////////////////////////////////////////////////////
    // Calculate where to start and end drawing the wall
    float wall_start = (HEIGHT / 2) - (wall_height / 2);
    float wall_end = wall_start + wall_height;


    // Pick texture based on hit direction
    t_texture *tex;
    if (hit_vertical)
    {
        if (cos_a > 0)
            tex = mlx->we_texture;
        else
            tex = mlx->ea_texture;
    }
    else
    {
        if (sin_a > 0)
            tex = mlx->no_texture;
        else
            tex = mlx->so_texture;
    }

    // Calculate texture X coordinate with more precision
    float tex_x;
    if (hit_vertical)
        tex_x = wall_y - floor(wall_y / BLOCK_SIZE) * BLOCK_SIZE;
    else
        tex_x = wall_x - floor(wall_x / BLOCK_SIZE) * BLOCK_SIZE;
    
    // Convert to texture coordinate space
    tex_x = tex_x * tex->width / BLOCK_SIZE;
    
    // Ensure texture coordinate is within bounds
    int texture_x = (int)tex_x % tex->width;
    if (texture_x < 0)
        texture_x += tex->width;

    // Draw vertical wall slice
    for (int y = wall_start; y < wall_end; y++)
    {
        if (y > 0 && y < HEIGHT && column > 0 && column < WIDTH)
        {
            // Calculate texture Y coordinate with proper scaling
            float ratio = (y - wall_start) / (wall_end - wall_start);
            int texture_y = ratio * tex->height;
            
            // Ensure texture coordinates are within bounds
            if (texture_y < 0)
                texture_y = 0;
            if (texture_y >= tex->height)
                texture_y = tex->height - 1;

            // Calculate texture position
            int tex_pos = texture_y * tex->width + texture_x;
            
            // Ensure we don't access outside the texture
            if (tex_pos >= 0 && tex_pos < (tex->width * tex->height) && tex->adr)
            {
                int color = tex->adr[tex_pos];
                put_pixel(column, y, mlx, color);
            }
        }
    }
}




int rgb_to_int(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

void    draw_world(t_mlx *mlx)
{
    int i = 0;
    int j = 0;
    while(i < WIDTH)
    {
        j = 0;
        while(j < HEIGHT)
        {
            if (j < HEIGHT / 2)
                put_pixel(i,j,mlx,0x019dde);
            else
                put_pixel(i,j,mlx,0x997663);
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
    draw_world(mlx);
    while(i < WIDTH)
    {
        draw_angle_view(mlx,start_ray,i);
        start_ray += angle_b_two_rays;
        i++;
    }
    draw_map(mlx);
    draw_square(mlx->player.x,mlx->player.y,10,0xFF0000,mlx);
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