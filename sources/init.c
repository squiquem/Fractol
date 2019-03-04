/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:07:15 by squiquem          #+#    #+#             */
/*   Updated: 2018/02/24 15:50:32 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftl.h"

t_pointd	*create_point(double x, double y)
{
	t_pointd	*p;

	if (!((p = (t_pointd*)malloc(sizeof(t_pointd)))))
		print_error("Error malloc");
	p->x = x;
	p->y = y;
	return (p);
}

static void	init_main(t_env *e)
{
	e->info = 0;
	e->mouse_stop = 0;
	e->a[0]->palette = get_palette();
	e->a[0]->max_iter = 32;
	e->a[0]->mouse = create_point(0, 0);
	e->a[0]->sharp = 256;
	e->a[0]->smooth = 0;
	e->a[0]->zoom = SCALE;
	e->a[0]->power = 2;
	e->a[0]->sizeimg = create_point(IMG_W, IMG_H);
	e->a[0]->center = create_point(IMG_W / 2, IMG_H / 2);
	e->a[0]->posimg = create_point(0, 0);
}

void		init(t_env *e)
{
	int			i;
	static char	*c[5] = {"mandelbrot", "julia", "burningship", "tricorn", \
							"newton"};

	i = 0;
	while (++i < 6)
	{
		e->a[i]->palette = get_palette();
		e->a[i]->max_iter = 32;
		e->a[i]->mouse = create_point(0, 0);
		e->a[i]->sharp = 256;
		e->a[i]->power = 2;
		e->a[i]->name = c[i - 1];
		e->a[i]->fractal = i - 1;
		e->a[i]->zoom = SCALE / 5;
		e->a[i]->smooth = 1;
		e->a[i]->sizeimg = create_point(WIN_W / 5, WIN_H / 5);
		e->a[i]->center = create_point(WIN_W / 10, WIN_H / 10);
		e->a[i]->posimg = create_point(IMG_W + 1, (i - 1) * IMG_H / 5);
	}
	init_main(e);
}
