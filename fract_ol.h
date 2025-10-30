/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakalkan <hakalkan@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:04:14 by hakalkan          #+#    #+#             */
/*   Updated: 2025/10/30 01:55:53 by hakalkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H
# include <unistd.h>
# include <stdlib.h>
# include "mlx.h"
# include "libft.h"
# define SIZE_X 800
# define SIZE_Y 800
# define MAX_ITER 100

typedef struct s_fract
{
	void    *mlx_ptr;
	void    *win_ptr;
	char    *title;
	void    *img;
	char    *addr;
	int     bits_per_pixel;
	int     size_line;
	int     endian;
	int     fractal_type;
	double  julia_re;
	double  julia_im;
	double  zoom;
	double  offset_x;
	double  offset_y;
	double	min_re;
	double	max_re;
	double	min_im;
	double	max_im;
}   t_fract;

void	render_mandelbrot(t_fract *f);
void	render_julia(t_fract *f);

#endif