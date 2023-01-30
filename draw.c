/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:43:04 by jdefayes          #+#    #+#             */
/*   Updated: 2023/01/30 17:10:38 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
# include "mlx/mlx.h"

int empty_square(t_img *img, t_square square);
int render_square(t_img *img, t_square square);
int render_background(t_img *img, int color);

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

	ft_center(&square.x, &square.y);
	i = square.y;
	j = square.x;
	while ( j < square.x + square.width)	// coor x + largeur, 100x + 50 largeur
	{
		t_img_ft_mlx_pixel_put(img, j++, i, square.color);
	}
	j = square.x;
	while (++i < square.y + (square.height - 1))
	{
		t_img_ft_mlx_pixel_put(img, j, i, square.color);
		t_img_ft_mlx_pixel_put(img, j + square.width, i, square.color);
		//printf("square.y:%d, i:%d\n", square.y, i); // >> sans\n -> boucle, avec \n -> pas de boucle, kamoulox.
	}
	while ( j < square.x + square.width)
	{
		t_img_ft_mlx_pixel_put(img, j++, i, square.color);
	}
	return(0);
}

int ft_center_f(double *x, double *y)
{
	*x = ((WID / 4) * 2) + (*x);
	*y = ((HEI / 4) * 2) - (*y);
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
			t_img_ft_mlx_pixel_put(img, j++, i, square.color);
		i++;
	}
	return (0);
}

int render_background(t_img *img, int color)
{
	int i;
	int j;

	i = 0;
	while (i < HEI)
	{
		j = 0;
		while (j < WID)
			t_img_ft_mlx_pixel_put(img, j++, i, color);
		i++;
	}
	return (0);
}
