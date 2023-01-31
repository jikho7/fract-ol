/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:41:09 by jdefayes          #+#    #+#             */
/*   Updated: 2023/01/31 17:53:28 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <complex.h>
# include "Libft/libft.h"

# define WID 500
# define HEI 500
# define RED 0xDC143C
# define BLUE 0x87CEEB
# define GREEN 0x90EE90
# define COLOR 0xAABFD1

typedef struct s_fra
{
	double x;
	double y;
	double height;
	double width;
	double row;
	double col;
	double c_r;
	double c_i;
	double x_new;
	int color;
	double z;
	double l_r;
	double u_d;
	int i;
	double multi_ju;
}	t_fra;

typedef struct s_square
{
	int	x;	// square's upper side corner
	int	y;	// square's upper side corner
	int width;
	int height;
	int color;
}	t_square;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_square	square;
	t_fra		fra;
	int			x;
	int			y;
	char**		av1;
}	t_data;

int mouse_controls(int mousecode, int x, int y, t_data *data);
int ft_center_f(double *x, double *y);
int mandelbrot(t_img *img, t_fra fra, t_data *data);
int conversion(double *x, double *y);
int ft_center(int *x, int *y);
int julia(t_img *img, t_fra fra, t_data *data);
int render(t_data *data);
void t_img_ft_mlx_pixel_put(t_img *img, int x, int y, int color);
int handle_input(int keycode, t_data *data);
int render(t_data *data);

#endif
