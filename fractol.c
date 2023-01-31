/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:05:01 by jdefayes          #+#    #+#             */
/*   Updated: 2023/01/31 17:54:36 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
# include "mlx/mlx.h"

int mouse_controls(int mousecode, int x, int y, t_data *data);
int mandelbrot(t_img *img, t_fra fra, t_data *data);
int render(t_data *data);
int	mlx_mouse_get_pos(void *win_ptr, int *x, int *y);
int julia(t_img *img, t_fra fra, t_data *data);
int ft_center(int *x, int *y);
int burning_ship(t_img *img, t_fra fra, t_data *data);
int	ft_atoi(const char *str);

int main(int argc, char**av)
{
	(void)argc;

	printf("Entrer type de fractal et un nombre.");
	printf("%s", av[1]);
	t_data	data;
	data.av1 = &av[1];
	data.fra =(t_fra){0, 0, 0, 0, 0, 0, 0, 0, 0, 0xAABFD1, 1, 1, 1, 0, -2};
	data.mlx = mlx_init();
	if(data.mlx == NULL)
		write(1, "error", 5);
	data.mlx_win = mlx_new_window(data.mlx, WID, HEI, "Fractal");
	data.img.img_ptr = mlx_new_image(data.mlx, WID, HEI);
	data.img.addr = mlx_get_data_addr(data.img.img_ptr, &data.img.bpp, &data.img.line_len, &data.img.endian);

	mlx_mouse_hook(data.mlx_win, &mouse_controls, &data);
	mlx_key_hook(data.mlx_win, &handle_input, &data);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_loop(data.mlx);

	//if(mlx_destroy_window(data.mlx, data.mlx_win))
	//	exit(0);
	//free(data.mlx);
	return (0);

//int		mlx_mouse_get_pos(void *win_ptr, int *x, int *y);
}

int render(t_data *data)
{
	if (data->mlx_win == NULL)
		exit(0);
	if(ft_atoi(*data->av1) == ft_atoi("burning_ship"))
		burning_ship(&data->img, data->fra, data);
	if(ft_atoi(*data->av1) == ft_atoi("mandelbrot"))
		mandelbrot(&data->img, data->fra, data);
	if(ft_atoi(*data->av1) == ft_atoi("julia"))
		julia(&data->img, data->fra, data);

	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img_ptr, 0, 0);
	return (0);
}

int handle_input(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	if(keycode == 124 && data->fra.z < 50)	//<-
		data->fra.l_r += 10 * data->fra.z;
	if(keycode == 124 && data->fra.z > 50)
		data->fra.l_r += 100;
	if(keycode == 123 && data->fra.z < 50)	//<-
		data->fra.l_r -= 10 * data->fra.z;
	if(keycode == 123 && data->fra.z > 50)
		data->fra.l_r -= 100;
	if(keycode == 125 && data->fra.z < 50)
		data->fra.u_d += 10 * data->fra.z;
	if(keycode == 125 && data->fra.z > 50)
		data->fra.u_d += 100;
	if(keycode == 126 && data->fra.z < 50)
		data->fra.u_d -= 10 * data->fra.z;
	if(keycode == 126 && data->fra.z > 50)
		data->fra.u_d -= 100;
	if (keycode == 49)
	{
		data->fra.multi_ju += 0.032;
		printf("multi: %f\n", data->fra.multi_ju);
	}
	return (0);
}

void t_img_ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
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
	if(mousecode == 2)
	{
		data->fra.u_d = 1;
		data->fra.l_r = 1;
		data->fra.z = 1;
	}
	if (mousecode == 5)
		data->fra.z *= 0.8;
	if (mousecode == 1)
		data->fra.color = data->fra.color + rand();
	if(mousecode == 3)
	{
		mlx_mouse_get_pos(data->mlx_win, &data->x, &data->y);
		//printf("y: %d\nx: %d\n", data->y, data->x);
		//printf("BEFORE U_D : %f\n", data->fra.u_d);
		//printf("L_R :%f\n", data->fra.l_r);
		data->fra.u_d = data->y;
		data->fra.l_r = data->x;
	//	printf("AFTER U_D : %f\n", data->fra.u_d);
		//printf("L_R :%f\n", data->fra.l_r);

	}

	return (0);
}


int mandelbrot(t_img *img, t_fra fra, t_data *data)
{
	(void)data;
	//printf("U_D : %f\n", fra.u_d);
	//printf("L_R :%f\n", fra.l_r);
	//printf("ZOOM :%f\n", fra.z);
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
        	while ((fra.x * fra.x)+(fra.y * fra.y) <= 4 && fra.i < 500)
			{
            	fra.x_new = (fra.x * fra.x) - (fra.y * fra.y) + fra.c_r;
            	fra.y = 2 * fra.x * fra.y + fra.c_i;
            	fra.x = fra.x_new;
            	fra.i++;
        	}
        	if (fra.i < 500)
				t_img_ft_mlx_pixel_put(img, fra.col, fra.row, fra.color + (fra.i * 11));
        	else
				t_img_ft_mlx_pixel_put(img, fra.col, fra.row, 0x00000000);
		}
	}
	return(0);
}

int julia(t_img *img, t_fra fra, t_data *data)
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
				t_img_ft_mlx_pixel_put(img, fra.col, fra.row, 0x00000000);
        	else
				t_img_ft_mlx_pixel_put(img, fra.col, fra.row, fra.color + (fra.i * 29.5));
		}
	}
	return(0);
}

/*

int render_triangle(t_img *img, t_square square)
{
	int y;
	int x;
	int t;
	int move;


    square.x = ((((WID / 2) - (WID / 2.0)) * 4.0) / WID);
    square.y = ((((HEI / 2)- (HEI / 2.0)) * 4.0) / HEI);

	t = square.width;		//	500
	//square.x = WID / 2;
	//square.y = HEI / 2;
	//square.y = HEI / 2;
	y = square.y;
	move = square.x;
	while (y < square.y + square.height )
	{
		x = move;
		while (x < (square.x + (square.width) - t) ) // x < 250 + 500 - 499 = 251 -- 249 < 249 + 500 - 498 = 251
		{
			t_img_ft_mlx_pixel_put(img, x, y, square.color);
			x++;
		}
		move--;
		t--;
		y++;
	}
	return (0);
}
*/

int burning_ship(t_img *img, t_fra fra, t_data *data)
{
	(void)data;
	//printf("U_D : %f\n", fra.u_d);
	//printf("L_R :%f\n", fra.l_r);
	//printf("ZOOM :%f\n", fra.z);
	while (fra.row++ < HEI + fra.height)
	{
		fra.col = 0;
		while (fra.col++ < WID + fra.width)	//Zn+1 = Zn2 + C
		{
       		fra.c_r = (((fra.col + fra.l_r - (WID / 2.0)) * 4.0) / WID / fra.z);	//	z = z2 + c
        	fra.c_i = (((fra.row + fra.u_d - (HEI / 2.0)) * 4.0) / HEI / fra.z);
			fra.x = 0;
			fra.y = 0;
       		fra.i = 0;
        	while ((fra.x * fra.x)+(fra.y * fra.y) <= 4 && fra.i < 500)
			{
            	fra.x_new = fabs((fra.x * fra.x)) - fabs((fra.y * fra.y)) + fra.c_r;
            	fra.y = fabs(2 * fra.x * fra.y) + fra.c_i;
            	fra.x = fra.x_new;
            	fra.i++;
        	}
        	if (fra.i < 500)
				t_img_ft_mlx_pixel_put(img, fra.col, fra.row, fra.color + (fra.i * 500));
        	else
				t_img_ft_mlx_pixel_put(img, fra.col, fra.row, 0x00000000);
		}
	}
	return(0);
}

/*
ft()
{
	for (int row = 0; row < height; row++)
	{
    	for (int col = 0; col < width; col++)
		{
        	double c_re = (col - width/2.0)*4.0/width;
        	double c_im = (row - height/2.0)*4.0/width;
        	double x = 0, y = 0;
        	int iteration = 0;
        	while (x*x+y*y <= 4 && iteration < max)
			{
            	double x_new = x*x - y*y + c_re;
            	y = 2*x*y + c_im;
            	x = x_new;
            	iteration++;
        	}
        	if (iteration < max) putpixel(col, row, white);
        	else putpixel(col, row, black);
   	 	}
	}
return(0);
}
*/


/*
int mandelbrot(t_img *img, t_frac frac, t_data *data)
{
	int it;
	scaled_mandelbrot (&frac);
	//printf("%d\n", frac.ptr_x);
	//printf("%d\n", frac.ptr_y);
	frac.width = frac.ptr_x;
	frac.height = frac.ptr_y;
	while (frac.row < frac.height)	// == i(0) < win_hei
	{
		frac.col = 0; // AJOUT
		while (frac.col < frac.width)	//== j(0) < win_wid
		{
       		frac.c_real = ((frac.col - (frac.ptr_x/2.0))*4.0)/frac.ptr_x;	//c = (0 - 500/2)*4/500 = -250*4/500 = -2
        	frac.c_imagi = ((frac.row - (frac.ptr_y/2.0))*4.0)/frac.ptr_x;	//c = (0 - 500/2)*4/500
			frac.x = 0;
			frac.y = 0;
        	while ((frac.x * frac.x)+(frac.y * frac.y) <= 4 && it < 400)	//x^ + y^ <= 4
			{
            	frac.x_new = (frac.x * frac.x) - (frac.y * frac.y) + frac.c_real;	//x,y = 1/ n_new = 0 + -2/ x_new = -2
            	frac.y = (2 * frac.x * frac.y) + frac.c_imagi;	//x,y = 1/ 2 + -2/ y = 0
            	frac.x = frac.x_new;
            	it++;
        	}
			if (it < 400)
				t_img_ft_mlx_pixel_put(img, frac.col, frac.row, frac.color + (it * 11));
        	else
				t_img_ft_mlx_pixel_put(img, frac.col, frac.row, 0x00000000);
			frac.col++;
			it = 0;
		}
		frac.row++;
	}
	return(0);
}
*/


int	handle_no_event(void *base)
{
	(void)base;
	return (0);
}

 int conversion(double *x_width, double *y_height)
 {
	*x_width = -2 + (*x_width / WID) * 4;
	*y_height = 2 + (*y_height / HEI) * 4;
	return (0);
 }
