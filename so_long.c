#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}				t_data;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;

}

int	key_close(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		mlx_clear_window(vars->mlx, vars->win);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	return (0);
}

int	button_close(t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

int	resize(int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	(void)vars;
	printf("The window is being resized\n");
	return (0);
}

int	main(void)
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "My window");
	img.img = mlx_new_image(vars.mlx, 640, 480);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	int i = 5;
	while (i++ <= 50)
		my_mlx_pixel_put(&img, 5, i, 0xFFFFFF);
	i = 5;
	while (i++ <= 50)
		my_mlx_pixel_put(&img, i, 5, 0xFFFFFF);
	i = 5;
	while (i++ <= 50)
		my_mlx_pixel_put(&img, 50, i, 0xFFFFFF);
	i = 5;
	while (i++ <= 50)
		my_mlx_pixel_put(&img, i, 50, 0xFFFFFF);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, key_close, &vars);
	mlx_hook(vars.win, 17, 0, button_close, &vars);
	mlx_hook(vars.win, 7, 1L<<4, resize, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
