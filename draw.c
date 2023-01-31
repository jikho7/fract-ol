/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:43:04 by jdefayes          #+#    #+#             */
/*   Updated: 2023/01/30 17:31:46 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
# include "mlx/mlx.h"

int ft_center_f(double *x, double *y);

int ft_center_f(double *x, double *y)
{
	*x = ((WID / 4) * 2) + (*x);
	*y = ((HEI / 4) * 2) - (*y);
	return (0);
}

