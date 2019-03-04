/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:34:11 by squiquem          #+#    #+#             */
/*   Updated: 2018/02/24 11:29:59 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftl.h"
#include <string.h>
#include <errno.h>

static void	draw_point(t_pointi *p, int color, t_img *e)
{
	int i;

	i = p->x * 4 + p->y * e->s_line;
	e->pixel_img[i] = color;
	e->pixel_img[++i] = color >> 8;
	e->pixel_img[++i] = color >> 16;
}

static void	*draw(void *e)
{
	t_pointi		start_end;
	t_pointi		z;
	pthread_t		s;
	static t_iter	(*frac[NB_FRACTALS])(t_pointi*, t_img*) = \
	{&mandelbrot, &julia, &burningship, &tricorn, &newton};

	start_end.x = 0;
	s = pthread_self();
	while (s != ((t_img*)e)->thr[start_end.x])
		start_end.x++;
	start_end.y = (start_end.x + 1) * ((t_img*)e)->sizeimg->x / NB_THR;
	start_end.x = start_end.x * ((t_img*)e)->sizeimg->x / NB_THR;
	z.y = ((t_img*)e)->sizeimg->y;
	while (--z.y)
	{
		z.x = start_end.x - 1;
		while (++z.x < start_end.y)
			draw_point(&z, get_color(e, \
			frac[((t_img*)e)->fractal](&z, e)), e);
	}
	pthread_exit(NULL);
}

void		reload_one(t_env *e, int j)
{
	int	rc;
	int	i;

	if (!(e->a[j]->img = mlx_new_image(e->mlx, e->a[j]->sizeimg->x, \
			e->a[j]->sizeimg->y)) ||
		!(e->a[j]->pixel_img = mlx_get_data_addr(e->a[j]->img, \
		&(e->a[j]->bpp), &(e->a[j]->s_line), &(e->a[j]->ed))))
		print_error("Error mlx");
	i = -1;
	while (++i < NB_THR)
		if ((rc = pthread_create(&e->a[j]->thr[i], NULL, draw, e->a[j])))
			ft_putendl_fd(strerror(errno), 2);
	i = -1;
	while (++i < NB_THR)
		if (pthread_join(e->a[j]->thr[i], NULL))
			ft_putendl_fd(strerror(errno), 2);
	mlx_put_image_to_window(e->mlx, e->win, e->a[j]->img, \
	e->a[j]->posimg->x, e->a[j]->posimg->y);
	mlx_destroy_image(e->mlx, e->a[j]->img);
	if (j == 0 && e->info)
		put_info(e);
}
