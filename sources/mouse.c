/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 23:22:16 by squiquem          #+#    #+#             */
/*   Updated: 2018/02/24 12:21:43 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftl.h"

int			mouse_move_hook(int x, int y, t_env *e)
{
	if (x < 0 || y < 0 || x > IMG_W || y > IMG_H || e->mouse_stop == 0 || \
	(e->a[0]->fractal != 1 && e->a[0]->fractal != 7 && e->a[0]->fractal != 8))
		return (0);
	e->a[0]->mouse->x = (x - e->a[0]->center->x) / e->a[0]->zoom;
	e->a[0]->mouse->y = (e->a[0]->center->y - y) / e->a[0]->zoom;
	e->a[2]->mouse->x = e->a[0]->mouse->x;
	e->a[2]->mouse->y = e->a[0]->mouse->y;
	reload_one(e, 0);
	reload_one(e, 2);
	return (0);
}

static void	mouse_key_zoom(int keycode, int x, int y, t_env *e)
{
	if (x < 0 || y < 0 || x > IMG_W || y > IMG_H ||
		(e->mouse_stop == 1 && e->a[0]->fractal == 1))
		return ;
	if (keycode == KEY_MOUSE_CLIC_L || keycode == MOUSE_ZOOM_IN)
	{
		e->a[0]->center->x += (IMG_W / 2 - x) / 4;
		e->a[0]->center->y += (IMG_H / 2 - y) / 4;
		e->a[0]->center->x = (e->a[0]->center->x - IMG_W / 2) * ZOOM_IN \
			+ IMG_W / 2;
		e->a[0]->center->y = (e->a[0]->center->y - IMG_H / 2) * ZOOM_IN \
			+ IMG_H / 2;
		e->a[0]->zoom *= ZOOM_IN;
	}
	if (keycode == KEY_MOUSE_CLIC_R || keycode == MOUSE_ZOOM_OUT)
	{
		e->a[0]->center->x -= (IMG_W / 2 - x) / 4;
		e->a[0]->center->y -= (IMG_H / 2 - y) / 4;
		e->a[0]->center->x = (e->a[0]->center->x - IMG_W / 2) * ZOOM_OUT \
			+ IMG_W / 2;
		e->a[0]->center->y = (e->a[0]->center->y - IMG_H / 2) * ZOOM_OUT \
			+ IMG_H / 2;
		e->a[0]->zoom *= ZOOM_OUT;
	}
}

static void	mouse_key_change(int keycode, int x, int y, t_env *e)
{
	if (y < 0 || x > WIN_W || x < 4 * WIN_W / 5 || y >= IMG_H)
		return ;
	if (keycode == KEY_MOUSE_CLIC_L)
	{
		e->a[0]->fractal = y / (WIN_H / 5);
		e->a[0]->name = e->a[y / (WIN_H / 5) + 1]->name;
		e->a[0]->center->x = e->a[0]->sizeimg->x / 2;
		e->a[0]->center->y = e->a[0]->sizeimg->y / 2;
		e->a[0]->zoom = SCALE;
		e->a[0]->max_iter = MAX_ITER;
		e->a[0]->power = 2;
	}
}

int			mouse_key_hook(int keycode, int x, int y, t_env *e)
{
	mouse_key_zoom(keycode, x, y, e);
	mouse_key_change(keycode, x, y, e);
	reload_one(e, 0);
	return (0);
}
