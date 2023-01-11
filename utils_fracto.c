#include "fractol.h"
# include "mlx/mlx.h"

void ft_mlx_pixel_put(t_data *data, int x, int y, int color);
int key_hook(int keycode, t_data *data);
int close_window(int keycode, t_data *var);
//int mouse_hook(int x, int y, t_data *var);
int	handle_no_event(void *base);

void ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

    dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(int *)dst = color;
}

int key_hook(int keycode, t_data*data)
{
	if(data == NULL)
		return(0);
	printf("Hello");
	printf("%c", keycode);
	return (0);
}

// int mouse_hook(int x, int y, t_data *var)
// {
// 	return (0);
// }
int	handle_no_event(void *base)
{
	if (base == NULL)
		return (0);
	return (0);
}

int close_window(int keycode, t_data *var)
{
	if (keycode == 52)
		mlx_destroy_window(var->mlx, var->mlx_win);
	printf("%d", keycode);
	return (0);
}

/*
ON_KEYDOWN	2	int (*f)(int keycode, void *param)
ON_KEYUP*	3	int (*f)(int keycode, void *param)
ON_MOUSEDOWN*	4	int (*f)(int button, int x, int y, void *param)
ON_MOUSEUP	5	int (*f)(int button, int x, int y, void *param)
ON_MOUSEMOVE	6	int (*f)(int x, int y, void *param)
ON_EXPOSE*	12	int (*f)(void *param)
ON_DESTROY	17	int (*f)(void *param)

Minilibx api has some alias hooking function:

mlx_expose_hook function is an alias of mlx_hook on expose event (12).
mlx_key_hook function is an alias of mlx_hook on key up event (3).
mlx_mouse_hook function is an alias of mlx_hook on mouse down event (4).


When  it catches an event, the MiniLibX calls the corresponding function with fixed parame-
   ters:

     expose_hook(void *param);
     key_hook(int keycode,void *param);
     mouse_hook(int button,int x,int y,void *param);
     loop_hook(void *param);
HORS MINILIBX
	 */
