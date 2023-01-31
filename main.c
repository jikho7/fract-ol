/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:21:04 by jdefayes          #+#    #+#             */
/*   Updated: 2023/02/01 00:21:08 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx/mlx.h"

int	main(int ac, char**av)
{
	t_data	data;

	if (ac == 1)
	{
		write(1, "Fractales:\n-> mandelbrot\n-> julia\n-> burning_ship\n", 50);
		exit(0);
	}
	else
	{
		data.av1 = &av[1];
		data.fra = (t_fra){0, 0, 0, 0, 0, 0, 0, 0, 0, 0xAABFD1, 1, 1, 1, 0, -2};
		data.mlx = mlx_init();
		if (data.mlx == NULL)
			write(1, "error", 5);
		data.mlx_win = mlx_new_window(data.mlx, WID, HEI, "Fractales");
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
