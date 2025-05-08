#include "parsing/header.h"
#include "raytracing/cub.h"

int	main(int ac, char *av[])
{
	
	t_data *data = NULL;
    t_mlx mlx;

	init_data(&data);
	if(data == NULL)
		exit(1);
	parsing(data ,ac ,av);
    init(&mlx,data);
    mlx.map = mapp(&mlx, data);
    init_player(&mlx);    
    mlx_hook(mlx.win,2,1L<<0,keyboard_on,&mlx);// why 2
    mlx_hook(mlx.win, 3, 1L<<1, keyboard_off, &mlx.player); // 3
    mlx_loop_hook(mlx.mlx,check_update,&mlx);
    // mlx_hook(mlx.win, 53, 0, close, &mlx);
    // mlx_hook(mlx.win, 17, 0, close, &mlx);
    mlx_loop(mlx.mlx);
    
}