/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:05:01 by jdefayes          #+#    #+#             */
/*   Updated: 2023/01/25 18:28:25 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
# include "mlx/mlx.h"

int mouse_controls(int mousecode, int x, int y, t_data *data);
int ft_putchar(int c);
int ft_center_f(double *x, double *y);
int mandelbrot(t_img *img, t_frac frac, t_data *data);
int	handle_no_event(void *base);
//int scaled_mandelbrot (t_frac *frac);
//int scaled_mandelbrot_2 (t_frac *frac, t_scaled *scaled);
int render_background(t_img *img, int color);
int	handle_no_event(void *base);
int conversion(double *x, double *y);

int main(void)
{
	t_data	data;
	t_frac	frac;
	data.frac =(t_frac){0, 0, 0, 0, 0, 0, 0, 0x90EE90, 0, 0, 0, 0};
	data.frac.zoom = 1;	//kamoulox
	data.mlx = mlx_init();
	if(data.mlx == NULL)
		write(1, "error", 5);
	data.mlx_win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "First window");
	data.img.img_ptr = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.img_ptr, &data.img.bpp, &data.img.line_len, &data.img.endian);
//	ft_center_f(&data.frac.x, &data.frac.y);
	//printf("CENTER DEBUT frac.x: %f\n frac.y: %f\n", data.frac.x, data.frac.y);
	//scaled_mandelbrot (&frac);
	mlx_mouse_hook(data.mlx_win, &mouse_controls, &data);
	//mlx_loop_hook(data.mlx, &handle_no_event, &data); //FONCTIONNE
	mlx_key_hook(data.mlx_win, &handle_input, &data); // FONCTIONNE
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_loop(data.mlx);

	free(data.mlx);
	return (0);
}

int render(t_data *data)
{
	if (data->mlx_win == NULL)
		return (1);
	mandelbrot(&data->img, data->frac, data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img_ptr, 0, 0);
	return (0);
}

int ft_center(int *x, int *y)
{
	*x = ((WINDOW_WIDTH / 4) * 2) + (*x);
	*y = ((WINDOW_HEIGHT / 4) * 2) - (*y);
	return (0);
}

int handle_input(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	if(keycode == 123)	//<-
	{
		data->frac.x += 20;
		data->frac.y += 0.8;
		//data->x -= 40;
	}
	if(keycode == 124)	// ->
	{
		data->x += 40;
	}

		if(keycode == 125)	//down
	{
		data->frac.row += 20;
		data->frac.height += 20;
		data->frac.col += 20;
		data->frac.width += 20;
	}
		if(keycode == 126)	//up
	{
		data->y += 40;
	}

	return (0);
}

void t_img_ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	if (x < WINDOW_WIDTH && x > 0 && y < WINDOW_HEIGHT && y > 0)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pixel = color;
	}
}

int mouse_controls(int mousecode, int x, int y, t_data *data)
{
	if (mousecode > 0 && mousecode < 10)
	{
		printf("%d\n", mousecode);
		printf("%d, %d\n", x, y);
		if (mousecode == 3)
		{
			mlx_destroy_window(data->mlx, data->mlx_win);
			exit(0);
		}
		if (mousecode == 4) // bas
			data->frac.zoom += 1.5;
		if (mousecode == 5) // haut
			data->frac.zoom *= 0.8;
		if (mousecode == 1)
			data->frac.color = data->frac.color + rand();
	}
	return (0);
}

int ft_center_f(double *x, double *y)
{
	*x = ((WINDOW_WIDTH / 4) * 2) + (*x);
	*y = ((WINDOW_HEIGHT / 4) * 2) - (*y);

	*x = -2 + (*x / WINDOW_WIDTH) * 4;
	*y = -2 + (*y / WINDOW_HEIGHT) * 4;
	return (0);
}

int render_square(t_img *img, t_square square)
{
	int i;
	int j;

	ft_center(&square.x, &square.y);
	i = square.y;
	while (i < square.y + square.height)
	{
		j = square.x;
		while (j < square.x + square.width)
			t_img_ft_mlx_pixel_put(img, j++, i, square.color);
		i++;
	}
	return (0);
}


int mandelbrot(t_img *img, t_frac frac, t_data *data)
{
	double it;
	double a;
	double b;
	//conversion(&frac.x, &frac.y);
	//printf("CONVERSION frac.x: %f\n frac.y: %f\n", frac.x, frac.y);
	//conversion(&frac.height, &frac.width);
	//printf("CONVERSION width: %f\n height: %f\n", frac.width, frac.height);
	printf("CENTER MAND frac.x: %f\n frac.y: %f\n", frac.x, frac.y);
	printf("ROW row: %f\n height: %f\n", frac.row, frac.height);
	while (frac.row < WINDOW_HEIGHT + frac.height)	// == i(0) < win_hei			//while (i < square.y + square.height)
	{
		frac.col = 0; // AJOUT
		while (frac.col < WINDOW_WIDTH + frac.width)	//== j(0) < win_wid		j = square.x; while (j < square.x + square.width)
		{
       		frac.c_real = ((frac.col - (WINDOW_WIDTH / 2.0)) * 4.0)/WINDOW_WIDTH / frac.zoom;	//c = (0 - 500/2)*4/500 = -250*4/500 = -2
        	frac.c_imagi = ((frac.row - (WINDOW_HEIGHT / 2.0)) * 4.0)/WINDOW_HEIGHT / frac.zoom;	//c = (0 - 500/2)*4/500
			a = 0;
			b = 0;
       		it = 0;
        	while ((a*a)+(b*b) <= 4 && it < 500)	//x^ + y^ <= 4
			{
            	frac.x_new = (a*a) - (b*b) + frac.c_real;	//x,y = 1/ n_new = 0 + -2/ x_new = -2
            	b = 2*a*b + frac.c_imagi;	//x,y = 1/ 2 + -2/ y = 0
            	a = frac.x_new;
				// if (it > 10)
				// {
				// 	t_img_ft_mlx_pixel_put(img, frac.col, frac.row, RED);
				// }
            	it++;
        	}
        	if (it < 500)
				t_img_ft_mlx_pixel_put(img, frac.col + frac.zoom, frac.row + frac.zoom, frac.color + (it * 11)); //DERNIER MODIF !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! FRAC.ZOOM ADDED
        	else
				t_img_ft_mlx_pixel_put(img, frac.col, frac.row, 0x00000000);
			frac.col++;
		}
		frac.row++;
	}
	return(0);
}

/*
int mandelbrot(t_img *img, t_frac frac, t_data *data) // VERSION BACKUP
{
	int it;
	double a;
	double b;
	conversion(&frac);
	printf("CONVERSION frac.x: %f\n frac.y: %f\n", frac.x, frac.y);

	ft_center_f(&frac.x, &frac.y);
	printf("CENTER frac.x: %f\n frac.y: %f\n", frac.x, frac.y);

	while (frac.row < frac.y + frac.height)	// == i(0) < win_hei			//while (i < square.y + square.height)
	{
		frac.col = 0; // AJOUT
		while (frac.col < frac.x + frac.width)	//== j(0) < win_wid		j = square.x; while (j < square.x + square.width)
		{
       		frac.c_real = ((frac.col - (frac.width/2.0))*4.0)/frac.width;	//c = (0 - 500/2)*4/500 = -250*4/500 = -2
        	frac.c_imagi = ((frac.row - (frac.height/2.0))*4.0)/frac.width;	//c = (0 - 500/2)*4/500
			a = 0;
			b = 0;
       		it = 0;
        	while ((a*a)+(b*b) <= 4 && it < 100)	//x^ + y^ <= 4
			{
            	frac.x_new = (a*a) - (b*b) + frac.c_real;	//x,y = 1/ n_new = 0 + -2/ x_new = -2
            	b = 2*a*b +frac.c_imagi;	//x,y = 1/ 2 + -2/ y = 0
            	a = frac.x_new;
				if (it > 10)
				{
					t_img_ft_mlx_pixel_put(img, frac.col, frac.row, RED);
				}
            	it++;
        	}
        	if (it < 100)
				t_img_ft_mlx_pixel_put(img, frac.col, frac.row, frac.color + (it * 11));
        	else
			{
				t_img_ft_mlx_pixel_put(img, frac.col, frac.row, 0x00000000);
			}
			frac.col++;
		}
		frac.row++;
	}
	return(0);
}
*/

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
// int scaled_mandelbrot (t_frac *frac)
// {

// 	if (WINDOW_WIDTH < WINDOW_HEIGHT || frac->width < frac->height)
// 	{
// 		frac->ptr_x = WINDOW_WIDTH;
// 		frac->ptr_y = WINDOW_WIDTH;
// 	}
// 	if (WINDOW_WIDTH == WINDOW_HEIGHT || frac->width == frac->height)
// 	{
// 		frac->ptr_x = WINDOW_WIDTH;
// 		frac->ptr_y = WINDOW_HEIGHT;
// 	}
// 	if (WINDOW_HEIGHT < WINDOW_WIDTH || frac->width > frac->height)
// 	{
// 		frac->ptr_y = WINDOW_HEIGHT;
// 		frac->ptr_x = WINDOW_HEIGHT;
// 	}

// 	return (0);
// }

// int scaled_mandelbrot_2 (t_frac *frac, t_scaled *scaled)
// {

// 	if (WINDOW_WIDTH < WINDOW_HEIGHT || frac->width < frac->height)
// 	{
// 		scaled->scaled_width = WINDOW_WIDTH;
// 		scaled->scaled_height = WINDOW_WIDTH;
// 	}
// 	if (WINDOW_WIDTH == WINDOW_HEIGHT || frac->width == frac->height)
// 	{
// 		scaled->scaled_width = WINDOW_WIDTH;
// 		scaled->scaled_height = WINDOW_WIDTH;
// 	}
// 	if (WINDOW_HEIGHT < WINDOW_WIDTH || frac->width > frac->height)
// 	{
// 		scaled->scaled_width = WINDOW_WIDTH;
// 		scaled->scaled_height = WINDOW_WIDTH;
// 	}

// 	return (0);
// }

int	handle_no_event(void *base)
{
	(void)base;
	return (0);
}

 int conversion(double *x_width, double *y_height)
 {
	*x_width = -2 + (*x_width / WINDOW_WIDTH) * 4;
	*y_height = 2 + (*y_height / WINDOW_HEIGHT) * 4;
	return (0);
 }

