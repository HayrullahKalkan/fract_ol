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

void	print_usage(void)
{
	ft_putstr_fd("Usage:\n", 1);
	ft_putstr_fd("  ./fract_ol Mandelbrot\n", 1);
	ft_putstr_fd("  ./fract_ol Julia <real> <imaginary>\n", 1);
	ft_putstr_fd("\nExamples:\n", 1);
	ft_putstr_fd("  ./fract_ol Mandelbrot\n", 1);
	ft_putstr_fd("  ./fract_ol Julia -0.7 0.27015\n", 1);
	ft_putstr_fd("  ./fract_ol Julia 0.285 0.01\n", 1);
	exit(1);
}

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

int mandel_much_iter(double c_re, double c_im, int max_iter)
{
    int i;
    double z_re;
    double z_im;
    double tmp;

	z_re = 0;
	i = 0;
    z_im = 0;
    while (i < max_iter)
    {
        tmp = z_re * z_re - z_im * z_im + c_re;
        z_im = 2 * z_re * z_im + c_im;
        z_re = tmp;
        if(z_re * z_re + z_im * z_im > 4)
            return (i);
        i++;
    }
    return (max_iter);
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
	*(unsigned int*)dst = color;
}
int	get_color(int iteration, int max_iter)
{
    int		r, g, b;
    double	t;

    if (iteration == max_iter)
        return (0x000000); // Siyah (set içinde)

    // Basit renk geçişi
    t = (double)iteration / max_iter;
    r = (int)(9 * (1 - t) * t * t * t * 255);
    g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
    b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
    
    return (r << 16 | g << 8 | b);
}
void	render_mandelbrot(t_fract *f)
{
	int	x;
	int y;
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
			my_mlx_pixel_put(f, x, y,get_color(iter, MAX_ITER));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img, 0, 0);
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
//zre= -0.7 zim)= 8.27015

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
			my_mlx_pixel_put(f, x, y, get_color(iter,MAX_ITER));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img, 0, 0);
}

double ft_atod(char *str)
{
    double  count;
    double  sign;
    double  a;
    int     i;

    i = 0;
    count = 0;
    sign  = 1;
    a = 0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
    if(str[i] == '-' || str[i] == '+')
    {
        if(str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] && str[i] != '.')
    {
        count = count * 10 + (str[i] - '0');
        i++; 
    }
    if (str[i] == '.')
        i++;
    while (str[i])
    {
        a = a + (str[i] - '0');
        a = a * 0.1;
        i++;
    }
    return ((count + a) * sign);
}

void checker(char **av, t_fract *f, int ac)
{
	if (!ft_strncmp(av[1], "Mandelbrot", ft_strlen(av[1])))
	{
		if (ac != 2)
			print_usage();
		f->fractal_type = 1;
		f->title = "Mandelbrot";
		f->zoom = 1.0;
		f->offset_x = 0.0;
		f->offset_y = 0.0;
	}
	else if (!ft_strncmp(av[1], "Julia", ft_strlen(av[1])))
	{
		if (ac != 4)
			print_usage();
		f->fractal_type = 2;
		f->julia_re = ft_atod(av[2]);
		f->julia_im = ft_atod(av[3]);
		f->title = "Julia";
		f->zoom = 1.0;
		f->offset_x = 0.0;
		f->offset_y = 0.0;
	}
	else
		print_usage();
}


int main(int ac, char **av)
{
	t_fract fractal;

	if(ac < 2)
		print_usage();
	checker(av, &fractal, ac);
	fractal.mlx_ptr = mlx_init();
	if (!fractal.mlx_ptr)
		return (1);
	fractal.win_ptr = mlx_new_window(fractal.mlx_ptr, SIZE_X, SIZE_Y, fractal.title);
	if (!fractal.win_ptr)
		return (1);
	fractal.img = mlx_new_image(fractal.mlx_ptr,SIZE_X,SIZE_Y);
	fractal.addr = mlx_get_data_addr(fractal.img, &fractal.bits_per_pixel,&fractal.size_line,&fractal.endian);
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
