/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:41:09 by jdefayes          #+#    #+#             */
/*   Updated: 2023/01/30 17:06:37 by jdefayes         ###   ########.fr       */
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

# define WID 500
# define HEI 500
# define MOUSEMOVE 6
//# define MOUSEPRESS 4
//# define MOUSERELEASE 5
# define KEYPRESS 2
# define KEYRELEASE 3
//# define ON_DESTROY 17
# define RED 0xDC143C
# define BLUE 0x87CEEB
# define GREEN 0x90EE90

typedef struct scaled
{
	int scaled_x;
	int scaled_y;
	int scaled_width;
	int scaled_height;
}	t_scaled;

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
}	t_fra;

typedef struct s_center
{
	int x;
	int y;
}	t_center;

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
	t_center	center;
	t_fra		fra;
	int			x;
	int			y;
}	t_data;

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);
int		key_hook(int keycode, t_data *data);
int		close_window(int keycode, t_data *var);
int		handle_no_event(void *base);
int		handle_input(int keycode, t_data *data);
int		write_keycode(int keycode, t_data *var);
int		empty_square(t_img *img, t_square square);
void	t_img_ft_mlx_pixel_put(t_img *img, int x, int y, int color);
int		render_square(t_img *img, t_square square);
int		render_background(t_img *img, int color);
int		render(t_data *data);
int		empty_square(t_img *img, t_square square);
int		ft_center(int *x, int *y);
int		julia(t_img *img, t_fra fra, t_data *data);

#endif
