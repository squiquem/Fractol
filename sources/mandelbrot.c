/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 02:02:00 by squiquem          #+#    #+#             */
/*   Updated: 2018/02/24 15:45:20 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftl.h"

static t_iter	mandelbrot2(t_pointi *c, t_img *a)
{
	int			j;
	t_pointd	tmp;
	t_iter		res;

	res.zn.x = 0;
	res.zn.y = 0;
	res.i = -1;
	while (res.zn.x * res.zn.x + res.zn.y * res.zn.y <= a->sharp \
			&& ++res.i < a->max_iter)
	{
		tmp = res.zn;
		j = 0;
		while (++j < a->power)
			res.zn = ft_cmul(tmp, res.zn);
		res.zn.x += (c->x - a->center->x) / a->zoom;
		res.zn.y += (a->center->y - c->y) / a->zoom;
	}
	return (res);
}

t_iter			mandelbrot(t_pointi *c, t_img *a)
{
	int			i;
	t_iter		res;
	t_pointd	z;
	t_pointd	zsqr;

	if (a->power != 2)
		return (mandelbrot2(c, a));
	z.x = 0;
	z.y = 0;
	zsqr.x = z.x * z.x;
	zsqr.y = z.y * z.y;
	i = -1;
	while (zsqr.x + zsqr.y <= a->sharp && ++i < a->max_iter)
	{
		z.y *= z.x;
		z.y += (a->center->y - c->y) / a->zoom + z.y;
		z.x = zsqr.x - zsqr.y + (c->x - a->center->x) / a->zoom;
		zsqr.x = z.x * z.x;
		zsqr.y = z.y * z.y;
	}
	res.i = i;
	res.zn.x = z.x;
	res.zn.y = z.y;
	return (res);
}

static t_iter	tricorn2(t_pointi *c, t_img *a)
{
	int			j;
	t_pointd	tmp;
	t_iter		res;

	res.zn.x = 0;
	res.zn.y = 0;
	res.i = -1;
	while (res.zn.x * res.zn.x + res.zn.y * res.zn.y <= a->sharp \
			&& ++res.i < a->max_iter)
	{
		res.zn = ft_conj(res.zn);
		tmp = res.zn;
		j = 0;
		while (++j < a->power)
			res.zn = ft_cmul(tmp, res.zn);
		res.zn.x += (c->x - a->center->x) / a->zoom;
		res.zn.y += (a->center->y - c->y) / a->zoom;
	}
	return (res);
}

t_iter			tricorn(t_pointi *c, t_img *a)
{
	int			i;
	t_iter		res;
	t_pointd	z;
	t_pointd	zsqr;

	if (a->power != 2)
		return (tricorn2(c, a));
	z.x = 0;
	z.y = 0;
	zsqr.x = z.x * z.x;
	zsqr.y = z.y * z.y;
	i = -1;
	while (zsqr.x + zsqr.y <= a->sharp && ++i < a->max_iter)
	{
		z.y *= z.x;
		z.y = (a->center->y - c->y) / a->zoom - 2 * z.y;
		z.x = zsqr.x - zsqr.y + (c->x - a->center->x) / a->zoom;
		zsqr.x = z.x * z.x;
		zsqr.y = z.y * z.y;
	}
	res.i = i;
	res.zn.x = z.x;
	res.zn.y = z.y;
	return (res);
}
