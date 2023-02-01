/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:41:09 by jdefayes          #+#    #+#             */
/*   Updated: 2023/02/01 17:16:00 by jdefayes         ###   ########.fr       */
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
# define RED 0xDC143C
# define BLUE 0x87CEEB
# define GREEN 0x90EE90
# define WHITE 0xffffff

typedef struct s_fra
{
	double	x;
	double	y;
	double	height;
	double	width;
	double	row;
	double	col;
	double	c_r;
	double	c_i;
	double	new;
	int		c;
	double	z;
	double	l_r;
	double	u_d;
	int		i;
	double	multi;
}	t_fra;

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
	void	*mlx;
	void	*mlx_win;
	t_img	img;
	t_fra	fra;
	int		x;
	int		y;
	char	**av1;
	int		len;
	int		check;

}	t_data;

int		main(int ac, char**av);
int		close_window(t_data *data);

int		mouse_controls(int mousecode, int x, int y, t_data *data);
int		handle_input(int keycode, t_data *data);

int		fra_strlen(const char *s);
int		fra_strncmp(const char *s1, const char *s2, size_t n);
int		render(t_data *data);
void	pixel_put(t_img *img, int x, int y, int color);
int		set_color(t_fra *fra, t_img *img);

int		mandelbrot(t_img *img, t_fra fra, t_data *data);
int		julia(t_img *img, t_fra fra, t_data *data);
int		burning_ship(t_img *img, t_fra fra);

void	reject(void);
#endif
