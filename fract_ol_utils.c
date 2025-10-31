/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakalkan <hakalkan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:57:18 by hakalkan          #+#    #+#             */
/*   Updated: 2025/10/30 01:25:55 by hakalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	mandel_much_iter(double c_re, double c_im, int max_iter)
{
	int		i;
	double	z_re;
	double	z_im;
	double	tmp;

	z_re = 0;
	z_im = 0;
	i = 0;
	while (i < max_iter)
	{
		tmp = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = tmp;
		if (z_re * z_re + z_im * z_im > 4)
			return (i);
		i++;
	}
	return (max_iter);
}

int	julia_much_iter(double z_re, double z_im, double c_re, double c_im)
{
	double	z_re_tmp;
	int		i;

	i = 0;
	while (i < MAX_ITER)
	{
		z_re_tmp = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = z_re_tmp;
		if (z_re * z_re + z_im * z_im > 4)
			return (i);
		i++;
	}
	return (MAX_ITER);
}

double	pixel_to_real(int x, int width, double min, double max)
{
	return (min + (double)x * (max - min) / width);
}

double	pixel_to_imag(int y, int height, double min, double max)
{
	return (min + (double)y * (max - min) / height);
}

void	my_mlx_pixel_put(t_fract *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
