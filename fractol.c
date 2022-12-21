/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:05:01 by jdefayes          #+#    #+#             */
/*   Updated: 2022/12/21 13:29:49 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fractol.h"

int main(void)
{
	//void	*mlx_ptr;
	//void 	*mlx_window;
	t_data = data; // ??

	data.mlx_ptr = mlx_init();
	if(data.mlx_ptr == NULL)
		write(1, "error", 5);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 500, 500, "coucou");
	if(data.win_ptr == NULL)
	{
		free(data.win_ptr);
		write(1, "error", 5);
	}
	mlx_loop(data.mlx_ptr);
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	free(data.mlx_ptr);
}
