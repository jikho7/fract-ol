/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:37:44 by jdefayes          #+#    #+#             */
/*   Updated: 2023/02/07 18:36:45 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx/mlx.h"

int	keyboard_input(int keycode, t_data *data)
{
	if (keycode == 53)						// esc
		reject();

	if (keycode == 124 && data->fra.z < 50)			// arrows pad
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

	if (keycode == 78)					// julia constant incre-decrementation
		data->fra.multi += 0.032;
	if (keycode == 69)
		data->fra.multi -= 0.032;
	return (0);
}

int	mouse_controls(int mousecode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (mousecode == 4 && data->fra.z <= 40)		//mandel/burn zoom in
		data->fra.z *= 1.2;
	if (mousecode == 4 && data->fra.z > 40)
		data->fra.z += 6;
	if (mousecode == 5)					// m/b zoom out
		data->fra.z *= 0.8;

	if (mousecode == 4)					// julia zoom
		data->z_julia *= 1.2;
	if (mousecode == 5)
		data->z_julia *= 0.8;

	if (mousecode == 2)					// reset, back to inital image
	{
		data->fra.u_d = 1;
		data->fra.l_r = 1;
		data->fra.z = 1;
		data->z_julia = 1;
	}

	if (mousecode == 1)					// to change colors
		data->fra.c = data->fra.c + rand();
	return (0);
}
