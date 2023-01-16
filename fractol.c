/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:05:01 by jdefayes          #+#    #+#             */
/*   Updated: 2023/01/16 15:46:51 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
# include "mlx/mlx.h"

void ft_mlx_pixel_put(t_data *data, int x, int y, int color);
void t_img_ft_mlx_pixel_put(t_img *img, int x, int y, int color);
int handle_input(int keycode, t_data *data);
int mouse_hook(int x, int y, t_data *var);
int	handle_no_event(void *base);
int write_keycode(int keycode, t_data *var);
int render_square(t_img *img, t_square square);
int render_background(t_img *img, int color);
int render(t_data *data);
int empty_square(t_img *img, t_square square);
int Sierpinski (t_img *img, t_square square);

int main(void)
{
	t_data	data;
	//int i;

	//i = 0;
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
		// HOOK PART //
	mlx_loop_hook(data.mlx, &render, &data);
	//mlx_loop_hook(data.mlx, &handle_no_event, &data); //FONCTIONNE
	//mlx_hook(data.mlx_win, 2, 0, &write_keycode, &data);
	//mlx_key_hook(data.mlx_win, &write_keycode, &data);
	mlx_key_hook(data.mlx_win, &handle_input, &data); // FONCTIONNE
	//mlx_expose_hook(&data);
	mlx_loop(data.mlx); //APRES FONCTIONS LOOP


	mlx_destroy_image(data.mlx, data.img.img_ptr);
	mlx_destroy_window(data.mlx, data.mlx_win);
	free(data.mlx);
	return (0);
}
/*
void ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

    dst = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
	*(int *)dst = color;
}
*/
void t_img_ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int handle_input(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	return (0);
}

int	handle_no_event(void *base)
{
	(void)base;
	return (0);
}

int render_square(t_img *img, t_square square)
{
	int i;
	int j;

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

int empty_square(t_img *img, t_square square)
{
	int i;
	int j;

	i = square.y;	// y	100
	j = square.x;	// x	100
	while ( j < square.width + square.x)
	{
		t_img_ft_mlx_pixel_put(img, j++, i, square.color);
	}
	j = square.x;
	while (++i < (square.height - 1) + square.y)
	{
		t_img_ft_mlx_pixel_put(img, j, i, square.color);
		t_img_ft_mlx_pixel_put(img, j + square.width, i, square.color);
	}
	while ( j < square.width + square.x)
	{
		t_img_ft_mlx_pixel_put(img, j++, i, square.color);
	}
return(0);
}

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
			{
				t_img_ft_mlx_pixel_put(img, j++, i, square.color);	// (t_img *img, int x, int y, int color);
			}
			i++;
		}
		//square.y = (((square.y / (3 ^ rep))) ^ 2) * (8 ^ rep);
		//square.x = (((square.x / (3 ^ rep))) ^ 2) * (8 ^ rep);
		k++;
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
		{
			t_img_ft_mlx_pixel_put(img, j++, i, color);
		}
		i++;
	}
	return (0);
}
// void ft_mlx_pixel_put(t_data *data, int x, int y, int color);
int render(t_data *data)
{
	if (data->mlx_win == NULL)
		return (1);
	render_background(&data->img, GREEN);
	//empty_square(&data->img, (t_square){WINDOW_WIDTH - 500, WINDOW_HEIGHT - 500, 100, 100, RED});
	Sierpinski(&data->img, (t_square){WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4, 800, 800, RED});
	//render_square(&data->img, (t_square){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, BLUE});
	//render_square(&data->img, (t_square){0, 0, 100, 100, RED});
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img_ptr, 0, 0);

	return (0);
}

/*
 int write_keycode(int keycode, t_data *var)
  {
  	(void)var;
 	if(keycode == 38)
  		printf("j");
	if(keycode == 0)
 		printf("a");
  	return (0);
  }
*/

/*
 int mouse_hook(int x, int y, t_data *var)
 {
 	return (0);
 }
 */
