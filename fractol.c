/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:05:01 by jdefayes          #+#    #+#             */
/*   Updated: 2023/01/10 22:16:35 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
# include "mlx/mlx.h"

void ft_mlx_pixel_put(t_data *data, int x, int y, int color);
int handle_input(int keycode, t_data *data);
int mouse_hook(int x, int y, t_data *var);
int	handle_no_event(void *base);
int write_keycode(int keycode, t_data *var);

int main(void)
{
	t_data	data;
	int i;

	i = 0;
	data.mlx = mlx_init();
	if(data.mlx == NULL)
		write(1, "error", 5);
	data.mlx_win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "First window");
	data.img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_len, &data.endian);


	while (i <= (WINDOW_WIDTH))
	{
		ft_mlx_pixel_put(&data, (WINDOW_WIDTH / 2) + (i * 2), WINDOW_HEIGHT / 2, 0x00FF0000);
		//ft_mlx_pixel_put(&data, WINDOW_WIDTH / 2 , (WINDOW_HEIGHT / 2) + (i * 2), 0x00FF0000);
		i++;
	}
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);

		// HOOK PART //
	mlx_loop_hook(data.mlx, &handle_no_event, &data); //FONCTIONNE
	//mlx_hook(data.mlx_win, 2, 0, &write_keycode, &data);
	//mlx_key_hook(data.mlx_win, &write_keycode, &data);
	mlx_key_hook(data.mlx_win, &handle_input, &data); // FONCTIONNE
	//mlx_expose_hook(&data);
	mlx_loop(data.mlx); //APRES FONCTIONS LOOP


	mlx_destroy_image(data.mlx, data.img);
	mlx_destroy_window(data.mlx, data.mlx_win);
	free(data.mlx);
	return (0);
}

void ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

    dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(int *)dst = color;
}

int handle_input(int keycode, t_data *data)
{
	if (keycode == 53)
		mlx_destroy_window(data->mlx, data->mlx_win);
	return (0);
}
/*
 int mouse_hook(int x, int y, t_data *var)
 {
 	return (0);
 }
 */
int	handle_no_event(void *base)
{
	(void)base;
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
