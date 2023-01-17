/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:43:04 by jdefayes          #+#    #+#             */
/*   Updated: 2023/01/17 13:49:53 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
# include "mlx/mlx.h"

void t_img_ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int empty_square(t_img *img, t_square square)
{
	int i;
	int j;

	ft_center(&square.x, &square.y);	// y	100
	i = square.y;	// 200
	j = square.x;	// 200
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
