/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:05:01 by jdefayes          #+#    #+#             */
/*   Updated: 2023/02/01 00:39:24 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx/mlx.h"

int	render(t_data *data)
{
	data->len = fra_strlen(*data->av1);
	data->check = fra_strncmp(*data->av1, "julia", 5);
	if (data->check == 0 && data->len == 5)
		julia (&data->img, data->fra, data);
	else if (data->len == 10)
	{
		data->check = fra_strncmp(*data->av1, "mandelbrot", 10);
		if (data->check == 0)
			mandelbrot (&data->img, data->fra, data);
		else
			reject();
	}
	else if (data->len == 12)
	{
		data->check = fra_strncmp(*data->av1, "burning_ship", 12);
		if (data->check == 0)
			burning_ship (&data->img, data->fra);
		else
			reject();
	}
	else
		reject();
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img_ptr, 0, 0);
	return (0);
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < WID && x > 0 && y < HEI && y > 0)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pixel = color;
	}
}

int	fra_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	fra_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	reject(void)
{
	write(1, "Fractales:\n-> mandelbrot\n-> julia\n-> burning_ship\n", 50);
	exit(0);
}
