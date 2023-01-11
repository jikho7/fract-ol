#ifndef FRACTOL_H
# define FRACTOL_H

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define MOUSEMOVE 6
# define MOUSEPRESS 4
# define MOUSERELEASE 5
# define KEYPRESS 2
# define KEYRELEASE 3

# include "mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <complex.h>

// typedef struct s_base
// {
// 	void	*mlx;
// 	void	*mlx_win;
// }	t_base;

typedef struct s_square
{
	int	x;	// square's upper side corner
	int	y;	// square's upper side corner
	int width;
	int hieght;
	int color;
}	t_square;

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	void	*win;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	t_square	square;
}	t_data;

typedef struct s_line
{
	void	*mlx_line;
}	t_line;



//void ft_mlx_pixel_put(t_data *data, int x, int y, int color);
// int key_hook(int keycode, t_base *data);
// int close_window(int keycode, t_base *var);
// int mouse_hook(int x, int y, t_data *var);
// int	handle_no_event(void *base);
#endif
