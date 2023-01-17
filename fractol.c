/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:05:01 by jdefayes          #+#    #+#             */
/*   Updated: 2023/01/17 18:50:08 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
# include "mlx/mlx.h"

int zoom(int mousecode, int x, int y, t_data *data);
int ft_putchar(int c);
//int write_keycode(int keycode, t_data *var);

int main(void)
{
	t_data	data;
	data.square = (t_square){-100, -100, 200, 200, BLUE, 1};
	data.mlx = mlx_init();
	if(data.mlx == NULL)
		write(1, "error", 5);
	data.mlx_win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "First window");
	data.img.img_ptr = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.img_ptr, &data.img.bpp, &data.img.line_len, &data.img.endian);

///////////////////////
	/*while (i <= (WINDOW_WIDTH))
	{
		ft_mlx_pixel_put(&data, (WINDOW_WIDTH / 2) + (i * 2), WINDOW_HEIGHT / 2, 0x00FF0000);
		//ft_mlx_pixel_put(&data, WINDOW_WIDTH / 2 , (WINDOW_HEIGHT / 2) + (i * 2), 0x00FF0000);
		i++;
	}
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img.img_ptr, 0, 0);
	*/
/////////////////////
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_mouse_hook(data.mlx_win, &zoom, &data);
	//mlx_loop_hook(data.mlx, &handle_no_event, &data); //FONCTIONNE
	mlx_key_hook(data.mlx_win, &handle_input, &data); // FONCTIONNE
	mlx_loop(data.mlx); //APRES FONCTIONS LOOP

	//mlx_destroy_image(data.mlx, data.img.img_ptr);
	//mlx_destroy_window(data.mlx, data.mlx_win);
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
		{
			t_img_ft_mlx_pixel_put(img, j++, i, square.color);	// (t_img *img, int x, int y, int color);
		}
		i++;
	}
	return (0);
}

/*
int Sierpinski (t_img *img, t_square square)
{
	int i;
	int j;
	int k;
	int rep;

	rep = 1;
	k = 0;
	i = square.y;	// y	100
	j = square.x;	// x	100
	while (k < rep)
	{
		//i = square.y;
		while (i < square.y + square.height)
		{
			j = square.x;
			while (j < square.x + square.width)
				t_img_ft_mlx_pixel_put(img, j++, i, square.color);	// (t_img *img, int x, int y, int color);
			i++;
		}
		//square.y = (((square.y / (3 ^ rep))) ^ 2) * (8 ^ rep);
		//square.x = (((square.x / (3 ^ rep))) ^ 2) * (8 ^ rep);
		k++;
	}

	return (0);
}
*/

int render_background(t_img *img, int color)
{
	int i;
	int j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			t_img_ft_mlx_pixel_put(img, j++, i, color);
		}
		i++;
	}
	return (0);
}

int render(t_data *data)
{
	if (data->mlx_win == NULL)
		return (1);
	render_background(&data->img, GREEN);
	empty_square(&data->img, data->square);
	//render_square(&data->img, (t_square){100, 100, 100, 100, RED, 1});
	//render_square(&data->img, (t_square){0, 0, 100, 100, RED, 1});
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img_ptr, 0, 0);

	return (0);
}

int ft_center(int *x, int *y)
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
	while ( j < square.width + square.x)
		t_img_ft_mlx_pixel_put(img, j++, i, square.color);
	j = square.x;
	while (++i < (square.height - 1) + square.y)
	{
		t_img_ft_mlx_pixel_put(img, j, i, square.color);
		t_img_ft_mlx_pixel_put(img, j + square.width, i, square.color);
	}
	while ( j < square.width + square.x)
		t_img_ft_mlx_pixel_put(img, j++, i, square.color);

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
	if (x < WINDOW_WIDTH && x > 0 && y < WINDOW_HEIGHT && y > 0)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pixel = color;
	}
}

int zoom(int mousecode, int x, int y, t_data *data)
{
	//if (mousecode > 0 && mousecode < 100)
	 //	printf("%d", mousecode);
	if (mousecode == 3)
	{
		printf("%d", mousecode);
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}

	if (mousecode == 4) // bas
	{
		//data->square.zoom = 2;
		//data->square.x -= 2 ;
		//data->square.y -=  2 ;
		data->square.width += 4;
		data->square.height += 4;
		//printf("%d\n", data->square.y);
	}
	 if (mousecode == 5) // haut
	 {
		data->square.width -= 4;
		data->square.height -= 4;
	 }
	return (0);
}

int ft_putchar(int c)
{
	write(1, &c, 2);
	return (0);
}

/*
int write_keycode(int keycode, t_data *var)
  {
  	(void)var;
	if (keycode != 53)
		ft_putchar(keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(var->mlx, var->mlx_win);
		exit(0);
	}
  	return (0);
  }
*/

