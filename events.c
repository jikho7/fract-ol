/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:40:50 by jdefayes          #+#    #+#             */
/*   Updated: 2023/01/17 13:43:46 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
# include "mlx/mlx.h"

// void ft_mlx_pixel_put(t_data *data, int x, int y, int color);
// int key_hook(int keycode, t_data *data);
// int close_window(int keycode, t_data *var);
// //int mouse_hook(int x, int y, t_data *var);
// int	handle_no_event(void *base);
// //int empty_square(t_img *img, t_square square);
// int mouse_hook(int x, int y, t_data *var);
// int handle_input(int keycode, t_data *data);
// int write_keycode(int keycode, t_data *var);
/*
void ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *pixel;

    pixel = data->img.addr + (y * data->img.line_len + x * (data->img.bpp / 8));
	*(int *)pixel = color;
}
*/

int key_hook(int keycode, t_data *data)
{
	if(data == NULL)
		return(0);
	printf("Hello");
	printf("%c", keycode);
	return (0);
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

int close_window(int keycode, t_data *var)
{
	if (keycode == 52)
		mlx_destroy_window(var->mlx, var->mlx_win);
	printf("%d", keycode);
	return (0);
}

/*
 int mouse_hook(int x, int y, t_data *var)
 {
 	return (0);
 }
*/

int write_keycode(int keycode, t_data *var)
  {
  	(void)var;
 	if(keycode == 38)
  		printf("j");
	if(keycode == 0)
 		printf("a");
  	return (0);
  }

/*
ON_KEYDOWN	2	int (*f)(int keycode, void *param)
ON_KEYUP*	3	int (*f)(int keycode, void *param)
ON_MOUSEDOWN*	4	int (*f)(int button, int x, int y, void *param)
ON_MOUSEUP	5	int (*f)(int button, int x, int y, void *param)
ON_MOUSEMOVE	6	int (*f)(int x, int y, void *param)
ON_EXPOSE*	12	int (*f)(void *param)
ON_DESTROY	17	int (*f)(void *param)

Minilibx api has some alias hooking function:

mlx_expose_hook function is an alias of mlx_hook on expose event (12).
mlx_key_hook function is an alias of mlx_hook on key up event (3).
mlx_mouse_hook function is an alias of mlx_hook on mouse down event (4).


When  it catches an event, the MiniLibX calls the corresponding function with fixed parame-
   ters:

     expose_hook(void *param);
     key_hook(int keycode,void *param);
     mouse_hook(int button,int x,int y,void *param);
     loop_hook(void *param);
HORS MINILIBX
	 */
	/*
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
*/
