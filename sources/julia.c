/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 02:02:00 by squiquem          #+#    #+#             */
/*   Updated: 2018/02/24 15:56:34 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftl.h"

static t_iter	julia2(t_pointi *c, t_img *a)
{
	int			j;
	t_pointd	tmp;
	t_iter		res;

	res.zn.x = (c->x - a->center->x) / a->zoom;
	res.zn.y = (a->center->y - c->y) / a->zoom;
	res.i = -1;
	while (res.zn.x * res.zn.x + res.zn.y * res.zn.y <= a->sharp \
			&& ++res.i < a->max_iter)
	{
		tmp = res.zn;
		j = 0;
		while (++j < a->power)
			res.zn = ft_cmul(res.zn, tmp);
		res.zn.x += a->mouse->x;
		res.zn.y += a->mouse->y;
	}
	return (res);
}

t_iter			julia(t_pointi *w, t_img *a)
{
	int			i;
	t_pointd	z;
	t_pointd	zsqr;
	t_iter		res;

	if (a->power != 2)
		return (julia2(w, a));
	z.x = (w->x - a->center->x) / a->zoom;
	z.y = (a->center->y - w->y) / a->zoom;
	zsqr.x = z.x * z.x;
	zsqr.y = z.y * z.y;
	i = 0;
	while (zsqr.x + zsqr.y <= a->sharp && i < a->max_iter)
	{
		z.y *= z.x;
		z.y += a->mouse->y + z.y;
		z.x = zsqr.x - zsqr.y + a->mouse->x;
		zsqr.x = z.x * z.x;
		zsqr.y = z.y * z.y;
		i++;
	}
	res.i = i;
	res.zn.x = z.x;
	res.zn.y = z.y;
	return (res);
}

static t_iter	burningship2(t_pointi *c, t_img *a)
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
		{
			res.zn = ft_cmul(res.zn, tmp);
			res.zn.y = fabs(res.zn.y);
		}
		res.zn.x += (c->x - a->center->x) / a->zoom;
		res.zn.y += (a->center->y - c->y) / a->zoom;
	}
	return (res);
}

t_iter			burningship(t_pointi *c, t_img *a)
{
	int			i;
	t_pointd	z;
	t_pointd	zsqr;
	t_iter		res;

	if (a->power != 2)
		return (burningship2(c, a));
	z.x = 0;
	z.y = 0;
	zsqr.x = z.x * z.x;
	zsqr.y = z.y * z.y;
	i = -1;
	while (zsqr.x + zsqr.y <= a->sharp && ++i < a->max_iter)
	{
		z.y = fabs(z.x) * fabs(z.y);
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

t_iter			newton(t_pointi *w, t_img *a)
{
	double		x;
	double		y;
	t_pointd	tmp;
	t_iter		res;

	if (w->x == (int)a->center->x && w->y == (int)a->center->y)
	{
		res = (t_iter){1, {1, 1}};
		return (res);
	}
	x = (w->x - a->center->x) / a->zoom;
	y = (a->center->y - w->y) / a->zoom;
	res.i = -1;
	while (x * x + y * y <= a->sharp && ++res.i < a->max_iter)
	{
		tmp.x = ((2 * pow(x, 3) - 6 * x * y * y + 1) * (x * x - y * y) + 4 * x
		* y * (3 * y * x * x - pow(y, 3))) / (3 * pow(x * x + y * y, 2));
		tmp.y = ((6 * x * x * y - 2 * y * y * y) * (x * x - y * y) - 2 * x * y
		* (2 * pow(x, 3) - 6 * x * y * y + 1)) / (3 * pow(x * x + y * y, 2));
		x = tmp.x;
		y = tmp.y;
	}
	res.zn.x = x;
	res.zn.y = y;
	return (res);
}
