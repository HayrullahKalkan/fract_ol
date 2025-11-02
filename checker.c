/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
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

int	is_valid_number(char *str)
{
	int	i;
	int	has_dot;

	i = 0;
	has_dot = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

double	ft_atod(char *str)
{
	int		i;
	double	sign;
	double	int_part;
	double	frac_part;
	double	div;

	i = 0;
	sign = 1.0;
	int_part = 0.0;
	frac_part = 0.0;
	div = 1.0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1.0;
		i++;
	}
	while (str[i] && str[i] != '.')
	{
		if (str[i] < '0' || str[i] > '9')
			break;
		int_part = int_part * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		frac_part = frac_part * 10.0 + (str[i] - '0');
		div *= 10.0;
		i++;
	}
	return ((int_part + frac_part / div) * sign);
}

void	init_mandelbrot(t_fract *f)
{
	f->fractal_type = 1;
	f->title = "Mandelbrot";
	f->zoom = 1.0;
	f->offset_x = 0.0;
	f->offset_y = 0.0;
}

void	init_julia(t_fract *f, char **av)
{
	if (!is_valid_number(av[2]) || !is_valid_number(av[3]))
	{
		ft_putstr_fd("Error: Invalid number format\n", 1);
		print_usage();
	}
	f->fractal_type = 2;
	f->julia_re = ft_atod(av[2]);
	f->julia_im = ft_atod(av[3]);
	f->title = "Julia";
	f->zoom = 1.0;
	f->offset_x = 0.0;
	f->offset_y = 0.0;
}

void	checker(char **av, t_fract *f, int ac)
{
	if (!ft_strncmp(av[1], "Mandelbrot", ft_strlen(av[1])))
	{
		if (ac != 2)
			print_usage();
		init_mandelbrot(f);
	}
	else if (!ft_strncmp(av[1], "Julia", ft_strlen(av[1])))
	{
		if (ac != 4)
			print_usage();
		init_julia(f, av);
	}
	else
		print_usage();
}
