/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:37:44 by jdefayes          #+#    #+#             */
/*   Updated: 2023/02/01 00:38:01 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx/mlx.h"

int	handle_input(int keycode, t_data *data)
{
	if (keycode == 53)
		reject();
	if (keycode == 124 && data->fra.z < 50)
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
	if (keycode == 78)
		data->fra.multi += 0.032;
	if (keycode == 69)
		data->fra.multi -= 0.032;
	return (0);
}

int	mouse_controls(int mousecode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (mousecode == 4 && data->fra.z <= 40)
		data->fra.z *= 1.2;
	if (mousecode == 4 && data->fra.z > 40)
		data->fra.z += 8;
	if (mousecode == 2)
	{
		data->fra.u_d = 1;
		data->fra.l_r = 1;
		data->fra.z = 1;
	}
	if (mousecode == 5)
		data->fra.z *= 0.8;
	if (mousecode == 1)
		data->fra.c = data->fra.c + rand();
	return (0);
}
