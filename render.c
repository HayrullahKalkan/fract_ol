/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakalkan <hakalkan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:57:18 by hakalkan          #+#    #+#             */
/*   Updated: 2025/10/30 01:25:55 by hakalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	get_color(int iteration, int max_iter)
{
	int		r;
	int		g;
	int		b;
	double	t;

	if (iteration == max_iter)
		return (0x000000);
	t = (double)iteration / max_iter;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return (r << 16 | g << 8 | b);
}

void	render_mandelbrot(t_fract *f)
{
	int		x;
	int		y;
	double	c_re;
	double	c_im;
	int		iter;

	f->min_re = -2.5 / f->zoom + f->offset_x;
	f->max_re = 1.0 / f->zoom + f->offset_x;
	f->min_im = -1.5 / f->zoom + f->offset_y;
	f->max_im = 1.5 / f->zoom + f->offset_y;
	y = 0;
	while (y < SIZE_Y)
	{
		x = 0;
		while (x < SIZE_X)
		{
			c_re = pixel_to_real(x, SIZE_X, f->min_re, f->max_re);
			c_im = pixel_to_imag(y, SIZE_Y, f->min_im, f->max_im);
			iter = mandel_much_iter(c_re, c_im, MAX_ITER);
			my_mlx_pixel_put(f, x, y, get_color(iter, MAX_ITER));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img, 0, 0);
}

void	render_julia(t_fract *f)
{
	int		x;
	int		y;
	double	z_re;
	double	z_im;
	int		iter;

	f->min_re = -2.0 / f->zoom + f->offset_x;
	f->max_re = 2.0 / f->zoom + f->offset_x;
	f->min_im = -2.0 / f->zoom + f->offset_y;
	f->max_im = 2.0 / f->zoom + f->offset_y;
	y = 0;
	while (y < SIZE_Y)
	{
		x = 0;
		while (x < SIZE_X)
		{
			z_re = pixel_to_real(x, SIZE_X, f->min_re, f->max_re);
			z_im = pixel_to_imag(y, SIZE_Y, f->min_im, f->max_im);
			iter = julia_much_iter(z_re, z_im, f->julia_re, f->julia_im);
			my_mlx_pixel_put(f, x, y, get_color(iter, MAX_ITER));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img, 0, 0);
}
