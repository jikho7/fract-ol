/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:05:01 by jdefayes          #+#    #+#             */
/*   Updated: 2023/01/23 15:33:26 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
# include "mlx/mlx.h"

int mouse_controls(int mousecode, int x, int y, t_data *data);
int ft_putchar(int c);
int ft_center_f(double *x, double *y);
int mandelbrot(t_img *img, t_mand mand);

int main(void)
{
	t_data	data;
	//data.square =(t_square){0, 0, 200, 200, BLUE};
	data.mand =(t_mand){0, 0, WINDOW_HEIGHT, WINDOW_WIDTH, 0, 0, 0, 0, 0};
	data.mlx = mlx_init();
	if(data.mlx == NULL)
		write(1, "error", 5);
	data.mlx_win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "First window");
	data.img.img_ptr = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.img_ptr, &data.img.bpp, &data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx, &render, &data);
	mlx_mouse_hook(data.mlx_win, &mouse_controls, &data);
	//mlx_loop_hook(data.mlx, &handle_no_event, &data); //FONCTIONNE
	mlx_key_hook(data.mlx_win, &handle_input, &data); // FONCTIONNE
	mlx_loop(data.mlx);

	free(data.mlx);
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
			t_img_ft_mlx_pixel_put(img, j++, i, square.color);	// (t_img *img, int x, int y, int color);
		i++;
	}
	return (0);
}

int render_background(t_img *img, int color)
{
	int i;
	int j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			t_img_ft_mlx_pixel_put(img, j++, i, color);
		i++;
	}
	return (0);
}

int render(t_data *data)
{
	if (data->mlx_win == NULL)
		return (1);
	//render_background(&data->img, GREEN);
	//empty_square(&data->img, data->square);
	//render_square(&data->img, data->square);
	//render_square(&data->img, data->square);
	mandelbrot(&data->img, data->mand);
	//empty_square(&data->img, data->square);
	//render_background(&data->img, GREEN);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img_ptr, 0, 0);
	return (0);
}

int ft_center(int *x, int *y)
{
	*x = ((WINDOW_WIDTH / 4) * 2) + (*x);
	*y = ((WINDOW_HEIGHT / 4) * 2) - (*y);
	return (0);
}

int ft_center_f(double *x, double *y)
{
	*x = ((WINDOW_WIDTH / 4) * 2) + (*x);
	*y = ((WINDOW_HEIGHT / 4) * 2) - (*y);
	return (0);
}
int empty_square(t_img *img, t_square square)
{
	int i;
	int j;

	ft_center(&square.x, &square.y);
	i = square.y;
	j = square.x;
	while ( j < square.x + square.width)	// coor x + largeur, 100x + 50 largeur
	{
		t_img_ft_mlx_pixel_put(img, j++, i, square.color);
	}
	j = square.x;
	while (++i < square.y + (square.height - 1))
	{
		t_img_ft_mlx_pixel_put(img, j, i, square.color);
		t_img_ft_mlx_pixel_put(img, j + square.width, i, square.color);
		//printf("square.y:%d, i:%d\n", square.y, i); // >> sans\n -> boucle, avec \n -> pas de boucle, kamoulox.
	}
	while ( j < square.x + square.width)
	{
		t_img_ft_mlx_pixel_put(img, j++, i, square.color);
	}

	return(0);
}

int handle_input(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		printf("%d", keycode);
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	return (0);
}

void t_img_ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	//if (x < WINDOW_WIDTH && x > 0 && y < WINDOW_HEIGHT && y > 0)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pixel = color;
	}
}

int mouse_controls(int mousecode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (mousecode > 0 && mousecode < 100)
		printf("%d\n", mousecode);
	if (mousecode == 3)
	{
		printf("%d", mousecode);
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	if (mousecode == 4) // bas
	{
		data->square.width += 4;
		data->square.height += 4;
		//printf("%d\n", data->square.y);
	}
	 if (mousecode == 5) // haut
	 {
		data->square.width -= 4;
		data->square.height -= 4;
	 }
	if (mousecode == 1)
		data->square.color = 0x00000000 + rand();	// <3
	return (0);
}

int ft_putchar(int c)
{
	write(1, &c, 2);
	return (0);
}


int mandelbrot(t_img *img, t_mand mand)
{
	int it;
	double x;
	double y;

	x = mand.x;
	y = mand.y;
	ft_center_f(&mand.x, &mand.y);
	while (mand.row < mand.height)	// == i(0) < win_hei
	{	//printf("DEBUT: mand.row:%d, mand.height:%d\n", mand.row, mand.height);

		mand.col = 0; // AJOUT
		while (mand.col < mand.width)	//== j(0) < win_wid
		{
       		mand.c_real = ((mand.col - (mand.width/2.0))*4.0)/mand.width;	//c = (0 - 500/2)*4/500 = -250*4/500 = -2
        	mand.c_imagi = ((mand.row - (mand.height/2.0))*4.0)/mand.width;	//c = (0 - 500/2)*4/500
			x = 0;
			y = 0;
       		it = 0;
			//printf("INIT XYI: 0\n");
        	while ((x*x)+(y*y) <= 4 && it < 50)	//x^ + y^ <= 4
			{
            	mand.x_new = (x*x) - (y*y) + mand.c_real;	//x,y = 1/ n_new = 0 + -2/ x_new = -2
            	y = 2*x*y + mand.c_imagi;	//x,y = 1/ 2 + -2/ y = 0
            	x = mand.x_new;
				//printf("c_real:%f, i:%d\n", mand.c_real, i);
				//printf("condition while:%d\n", (x*x)+(y*y));
            	it++;
        	}
        	if (it < 50)
				t_img_ft_mlx_pixel_put(img, mand.col, mand.row, GREEN);
        	else
			{
				t_img_ft_mlx_pixel_put(img, mand.col, mand.row, BLUE);
			}
			mand.col++;
			//printf("col:%d, i:%d\n",mand.col, i);
		}

		mand.row++;
		//printf("row:%d\n",mand.row);
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
int mandelbrot(t_img *img, t_mand mand)
{
	int i;
	double x;
	double y;

	x = mand.x;
	y = mand.y;
	ft_center_f(&mand.x, &mand.y);
	while (mand.row < mand.height)
	{	//printf("DEBUT: mand.row:%d, mand.height:%d\n", mand.row, mand.height);
		while (mand.col < mand.width)
		{
       		mand.c_real = ((mand.col - (mand.width/2))*4)/mand.width;	//c = (0 - 500/2)*4/500 = -250*4/500 = -2
        	mand.c_imagi = ((mand.row - (mand.height/2))*4)/mand.width;	//c = (0 - 500/2)*4/500
			x = 0;
			y = 0;
       		i = 0;
			//printf("INIT XYI: 0\n");
        	while ((x*x)+(y*y) <= 4 && i < 5000)	//x^ + y^ <= 4
			{
            	mand.x_new = (x*x) - (y*y) + mand.c_real;	//x,y = 1/ n_new = 0 + -2/ x_new = -2
            	y = 2*x*y + mand.c_imagi;	//x,y = 1/ 2 + -2/ y = 0
            	x = mand.x_new;
				//printf("c_real:%f, i:%d\n", mand.c_real, i);
				//printf("condition while:%d\n", (x*x)+(y*y));
            	i++;
        	}
        	if (i < 5000)
				t_img_ft_mlx_pixel_put(img, mand.col, mand.row, RED);
        	else
			{
				t_img_ft_mlx_pixel_put(img, mand.col, mand.row, BLUE);
			}
			mand.col++;
			//printf("col:%d, i:%d\n",mand.col, i);
		}
		mand.row++;
		//printf("row:%d\n",mand.row);
	}
	return(0);
}
*/
