/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakalkan <hakalkan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:57:18 by hakalkan          #+#    #+#             */
/*   Updated: 2025/10/30 01:25:55 by hakalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	close_window(t_fract *f)
{
	mlx_destroy_image(f->mlx_ptr, f->img);
	mlx_destroy_window(f->mlx_ptr, f->win_ptr);
	mlx_destroy_display(f->mlx_ptr);
	free(f->mlx_ptr);
	exit(0);
	return (0);
}

int	handle_key(int keycode, t_fract *f)
{
	double	move_step;

	move_step = 0.5 / f->zoom;
	if (keycode == 65307)
		close_window(f);
	else if (keycode == 65361 || keycode == 97)
		f->offset_x -= move_step;
	else if (keycode == 65363 || keycode == 100)
		f->offset_x += move_step;
	else if (keycode == 65362 || keycode == 119)
		f->offset_y -= move_step;
	else if (keycode == 65364 || keycode == 115)
		f->offset_y += move_step;
	else
		return (0);
	if (f->fractal_type == 1)
		render_mandelbrot(f);
	else if (f->fractal_type == 2)
		render_julia(f);
	return (0);
}

int	handle_mouse(int button, int x, int y, t_fract *f)
{
	double	zoom_factor;

	(void)x;
	(void)y;
	zoom_factor = 1.2;
	if (button == 4)
		f->zoom *= zoom_factor;
	else if (button == 5)
		f->zoom /= zoom_factor;
	else
		return (0);
	if (f->fractal_type == 1)
		render_mandelbrot(f);
	else if (f->fractal_type == 2)
		render_julia(f);
	return (0);
}

void	init_fractal(t_fract *fractal)
{
	fractal->mlx_ptr = mlx_init();
	if (!fractal->mlx_ptr)
		exit(1);
	fractal->win_ptr = mlx_new_window(fractal->mlx_ptr, SIZE_X, SIZE_Y,
			fractal->title);
	if (!fractal->win_ptr)
		exit(1);
	fractal->img = mlx_new_image(fractal->mlx_ptr, SIZE_X, SIZE_Y);
	fractal->addr = mlx_get_data_addr(fractal->img,
			&fractal->bits_per_pixel, &fractal->size_line, &fractal->endian);
}

int	main(int ac, char **av)
{
	t_fract	fractal;

	if (ac < 2)
		print_usage();
	checker(av, &fractal, ac);
	init_fractal(&fractal);
	if (fractal.fractal_type == 1)
		render_mandelbrot(&fractal);
	else if (fractal.fractal_type == 2)
		render_julia(&fractal);
	mlx_key_hook(fractal.win_ptr, handle_key, &fractal);
	mlx_mouse_hook(fractal.win_ptr, handle_mouse, &fractal);
	mlx_hook(fractal.win_ptr, 17, 0, close_window, &fractal);
	mlx_loop(fractal.mlx_ptr);
	return (0);
}
