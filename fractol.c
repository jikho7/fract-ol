/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:05:01 by jdefayes          #+#    #+#             */
/*   Updated: 2023/01/31 23:18:13 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx/mlx.h"

int	mouse_controls(int mousecode, int x, int y, t_data *data);
int	mandelbrot(t_img *img, t_fra fra, t_data *data);
int	render(t_data *data);
int	mlx_mouse_get_pos(void *win_ptr, int *x, int *y);
int	julia(t_img *img, t_fra fra, t_data *data);
int	burning_ship(t_img *img, t_fra fra, t_data *data);
int	fra_strncmp(const char *s1, const char *s2, size_t n);
int	fra_strlen(const char *s);
void	reject(void);

int	main(int ac, char**av)
{
	t_data	data;

	if (ac == 1)
	{
		printf("Fractals:\n-> mandelbrot\n-> julia\n-> burning_ship\n");
		exit(0);
	}
	else
	{
		data.av1 = &av[1];
		data.fra = (t_fra){0, 0, 0, 0, 0, 0, 0, 0, 0, 0xAABFD1, 1, 1, 1, 0, -2};
		data.mlx = mlx_init();
		if (data.mlx == NULL)
			write(1, "error", 5);
		data.mlx_win = mlx_new_window(data.mlx, WID, HEI, "Fractal");
		data.img.img_ptr = mlx_new_image(data.mlx, WID, HEI);
		data.img.addr = mlx_get_data_addr(data.img.img_ptr, &data.img.bpp,
				&data.img.line_len, &data.img.endian);
		mlx_mouse_hook(data.mlx_win, &mouse_controls, &data);
		mlx_key_hook(data.mlx_win, &handle_input, &data);
		mlx_loop_hook(data.mlx, &render, &data);
		mlx_loop(data.mlx);
	}
	return (0);
}

int	render(t_data *data)
{
	data->len = fra_strlen(*data->av1);
	data->check = fra_strncmp(*data->av1, "julia", 5);
	if (data->check == 0 && data->len == 5)
		julia (&data->img, data->fra, data);
	else if (data->len == 10)
	{
		data->check = fra_strncmp(*data->av1, "mandelbrot", 10);
		if (data->check == 0)
			mandelbrot (&data->img, data->fra, data);
		else
			reject();
	}
	else if (data->len == 12)
	{
		data->check = fra_strncmp(*data->av1, "burning_ship", 12);
		if (data->check == 0)
			burning_ship (&data->img, data->fra, data);
		else
			reject();
	}
	else
		reject();
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img_ptr, 0, 0);
	return (0);
}

int	handle_input(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	if (keycode == 124 && data->fra.z < 50)
		data->fra.l_r += 10 * data->fra.z;
	if (keycode == 124 && data->fra.z > 50)
		data->fra.l_r += 100;
	if (keycode == 123 && data->fra.z < 50)
		data->fra.l_r -= 10 * data->fra.z;
	if (keycode == 123 && data->fra.z > 50)
		data->fra.l_r -= 100;
	if (keycode == 125 && data->fra.z < 50)
		data->fra.u_d += 10 * data->fra.z;
	if (keycode == 125 && data->fra.z > 50)
		data->fra.u_d += 100;
	if (keycode == 126 && data->fra.z < 50)
		data->fra.u_d -= 10 * data->fra.z;
	if (keycode == 126 && data->fra.z > 50)
		data->fra.u_d -= 100;
	if (keycode == 49)
	{
		data->fra.multi_ju += 0.032;
		printf("multi: %f\n", data->fra.multi_ju);
	}
	return (0);
}

void pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < WID && x > 0 && y < HEI && y > 0)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pixel = color;
	}
}

int mouse_controls(int mousecode, int x, int y, t_data *data)
{
	printf("x:%d\n y:%d\n", x, y);
	if (mousecode == 4 && data->fra.z <= 40)
		data->fra.z *= 1.2;
	if (mousecode == 4 && data->fra.z > 40)
		data->fra.z += 8;
	if (mousecode == 2)
	{
		data->fra.u_d = 1;
		data->fra.l_r = 1;
		data->fra.z = 1;
	}
	if (mousecode == 5)
		data->fra.z *= 0.8;
	if (mousecode == 1)
		data->fra.c = data->fra.c + rand();
	 if(mousecode == 3)
	 {
	 	mlx_mouse_get_pos(data->mlx_win, &data->x, &data->y);
	 	printf("y: %d\nx: %d\n", data->y, data->x);
	 	printf("BEFORE U_D : %f\n", data->fra.u_d);
	 	printf("L_R :%f\n", data->fra.l_r);
	 	data->fra.u_d = data->y;
	 	data->fra.l_r = data->x;
	 	printf("AFTER U_D : %f\n", data->fra.u_d);
	 	printf("L_R :%f\n", data->fra.l_r);

	 }

	return (0);
}


int	mandelbrot(t_img *img, t_fra fra, t_data *data)
{
	(void)data;
	while (fra.row++ < HEI + fra.height)
	{
		fra.col = 0;
		while (fra.col++ < WID + fra.width)
		{
			fra.c_r = (((fra.col + fra.l_r - (WID / 2.0)) * 4.0) / WID / fra.z);
			fra.c_i = (((fra.row + fra.u_d - (HEI / 2.0)) * 4.0) / HEI / fra.z);
			fra.x = 0;
			fra.y = 0;
			fra.i = 0;
			while ((fra.x * fra.x) + (fra.y * fra.y) <= 4 && fra.i < 500)
			{
				fra.x_new = (fra.x * fra.x) - (fra.y * fra.y) + fra.c_r;
				fra.y = 2 * fra.x * fra.y + fra.c_i;
				fra.x = fra.x_new;
				fra.i++;
			}
			if (fra.i < 500)
				pixel_put(img, fra.col, fra.row, fra.c + (fra.i * 9));
			else
				pixel_put(img, fra.col, fra.row, 0x00000000);
		}
	}
	return (0);
}

int	julia(t_img *img, t_fra fra, t_data *data)
{
	(void)data;
	while (fra.row++ < WID + fra.height)
	{
		fra.col = 0;
		while (fra.col++ < HEI + fra.width)
		{
	   		fra.c_r = (((fra.col + fra.l_r - (WID / 2.0)) * 4.0) / WID / fra.z);
			fra.c_i = (((fra.row + fra.u_d - (HEI / 2.0)) * 4.0) / HEI / fra.z);
			//fra.x = 1;
			//fra.y = 1;
	   		fra.i = 0;
			while ((fra.c_r * fra.c_r)+(fra.c_i * fra.c_i) <= 4 && fra.i < 500)
			{
				fra.x_new = (fra.c_r * fra.c_r) - (fra.c_i * fra.c_i) + fra.multi_ju;
				fra.c_i = 2 * fra.c_r * fra.c_i + fra.multi_ju;
				fra.c_r = fra.x_new;
				fra.i++;
			}
			if (fra.i == 500)
				pixel_put(img, fra.col, fra.row, 0x00000000);
			else
				pixel_put(img, fra.col, fra.row, fra.c + (fra.i * 29.5));
		}
	}
	return(0);
}

int burning_ship(t_img *img, t_fra fra, t_data *data)
{
	(void)data;

	while (fra.row++ < HEI + fra.height)
	{
		fra.col = 0;
		while (fra.col++ < WID + fra.width)
		{
			fra.c_r = (((fra.col + fra.l_r - (WID / 2.0)) * 4.0) / WID / fra.z);
			fra.c_i = (((fra.row + fra.u_d - (HEI / 2.0)) * 4.0) / HEI / fra.z);
			fra.x = 0;
			fra.y = 0;
			fra.i = 0;
			while ((fra.x * fra.x) + (fra.y * fra.y) <= 4 && fra.i < 500)
			{
				fra.x_new = fabs((fra.x * fra.x)) - fabs((fra.y * fra.y)) + fra.c_r;
				fra.y = fabs(2 * fra.x * fra.y) + fra.c_i;
				fra.x = fra.x_new;
				fra.i++;
			}
			if (fra.i < 500)
				pixel_put(img, fra.col, fra.row, fra.c + (fra.i * 500));
			else
				pixel_put(img, fra.col, fra.row, 0x00000000);
		}
	}
	return (0);
}

int	fra_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	fra_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void reject(void)
{
	printf("Fractals:\n-> mandelbrot\n-> julia\n-> burning_ship\n");
	exit(0);
}
