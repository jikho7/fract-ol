/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractales.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:22:14 by jdefayes          #+#    #+#             */
/*   Updated: 2023/02/07 18:21:51 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx/mlx.h"

int	mandelbrot(t_img *img, t_fra fra, t_data *data) // different constants (c_r, c_i)
{
	(void)data;
	while (fra.row++ < HEI)
	{
		fra.col = 0;
		while (fra.col++ < WID)
		{
			fra.c_r = (((fra.col + fra.l_r - (WID / 2.0)) * 4.0) / WID / fra.z);	// conversion from pixel position to coordinates (-2;2 plan)
			fra.c_i = (((fra.row + fra.u_d - (HEI / 2.0)) * 4.0) / HEI / fra.z);
			fra.x = 0;
			fra.y = 0;
			fra.i = 0;
			while ((fra.x * fra.x) + (fra.y * fra.y) <= 4 && fra.i < 400)
			{
				fra.new = (fra.x * fra.x) - (fra.y * fra.y) + fra.c_r;		// fractal formula
				fra.y = 2 * fra.x * fra.y + fra.c_i;
				fra.x = fra.new;
				fra.i++;
			}
			set_color (&fra, img);
		}
	}
	return (0);
}

int	julia(t_img *img, t_fra fra, t_data *data)	// same constants (multi)
{
	while (fra.row++ < WID)
	{
		fra.col = 0;
		while (fra.col++ < HEI)
		{
			fra.c_r = (((fra.col + fra.l_r - (WID / 2.0)) * 4.0) / WID
					/ data->z_julia);
			fra.c_i = (((fra.row + fra.u_d - (HEI / 2.0)) * 4.0)
					/ HEI / data->z_julia);
			fra.i = 0;
			while ((fra.c_r * fra.c_r) + (fra.c_i * fra.c_i)
				<= 4 && fra.i < 400)
			{
				fra.new = (fra.c_r * fra.c_r) - (fra.c_i * fra.c_i) + fra.multi;
				fra.c_i = 2 * fra.c_r * fra.c_i + fra.multi;
				fra.c_r = fra.new;
				fra.i++;
			}
			set_color(&fra, img);
		}
	}
	return (0);
}

int	burning_ship(t_img *img, t_fra fra)	// same as Mandel, absolute values (fabs)
{
	while (fra.row++ < HEI)
	{
		fra.col = 0;
		while (fra.col++ < WID)
		{
			fra.c_r = (((fra.col + fra.l_r - (WID / 2.0)) * 4.0) / WID / fra.z);
			fra.c_i = (((fra.row + fra.u_d - (HEI / 2.0)) * 4.0) / HEI / fra.z);
			fra.x = 0;
			fra.y = 0;
			fra.i = 0;
			while ((fra.x * fra.x) + (fra.y * fra.y) <= 4 && fra.i < 400)
			{
				fra.new = fabs((fra.x * fra.x)) - fabs((fra.y * fra.y))
					+ fra.c_r;
				fra.y = fabs(2 * fra.x * fra.y) + fra.c_i;
				fra.x = fra.new;
				fra.i++;
			}
			set_color (&fra, img);
		}
	}
	return (0);
}
