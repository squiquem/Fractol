/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:09:49 by squiquem          #+#    #+#             */
/*   Updated: 2018/02/24 15:44:47 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftl.h"

static void	key_hook_change(int keycode, t_env *e)
{
	if (keycode == KEY_UP)
		e->a[0]->center->y += MOVE;
	else if (keycode == KEY_DOWN)
		e->a[0]->center->y -= MOVE;
	else if (keycode == KEY_LEFT)
		e->a[0]->center->x += MOVE;
	else if (keycode == KEY_RIGHT)
		e->a[0]->center->x -= MOVE;
	else if (keycode == KEYPAD_PLUS)
		e->a[0]->max_iter *= 2;
	else if (keycode == KEYPAD_MINUS && e->a[0]->max_iter > 2)
		e->a[0]->max_iter /= 2;
	if (keycode == KEY_DELETE && e->a[0]->fractal != 4)
		e->a[0]->smooth = !(e->a[0]->smooth);
	if (keycode == KEY_PAGE_UP && e->a[0]->sharp < 16384)
		e->a[0]->sharp *= 2;
	if (keycode == KEY_PAGE_DOWN && e->a[0]->sharp > 1)
		e->a[0]->sharp /= 2;
}

static void	key_hook_end(int keycode, t_env *e)
{
	if (keycode == KEY_ENTER)
	{
		e->a[0]->center->x = e->a[0]->sizeimg->x / 2;
		e->a[0]->center->y = e->a[0]->sizeimg->y / 2;
		e->a[0]->zoom = SCALE;
		e->a[0]->max_iter = MAX_ITER;
	}
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(e->mlx, e->win);
		free(e);
		exit(1);
	}
	if (keycode == KEY_SPACE)
		e->mouse_stop = !(e->mouse_stop);
	if (keycode == KEY_F12)
		e->info = !(e->info);
}

static void	key_hook_color(int keycode, t_env *e)
{
	if (keycode >= KEYPAD_0 && keycode <= KEYPAD_0 + 7)
		e->a[0]->palette = &get_palette()[keycode - KEYPAD_0];
	if (keycode == KEYPAD_8)
		e->a[0]->palette = &get_palette()[8];
	if (keycode == KEYPAD_9)
		e->a[0]->palette = &get_palette()[9];
	if (keycode == KEY_SUPPR)
	{
		e->a[0]->palette->cycle /= 10;
		e->a[0]->palette->cycle = !(e->a[0]->palette->cycle);
		e->a[0]->palette->cycle *= 10;
	}
	e->a[1]->palette = e->a[0]->palette;
	e->a[2]->palette = e->a[0]->palette;
	e->a[3]->palette = e->a[0]->palette;
	e->a[4]->palette = e->a[0]->palette;
	e->a[5]->palette = e->a[0]->palette;
	reload_one(e, 1);
	reload_one(e, 2);
	reload_one(e, 3);
	reload_one(e, 4);
	reload_one(e, 5);
}

static void	key_hook_heads(int keycode, t_env *e)
{
	if (keycode == KEY_F1)
		e->a[0]->power++;
	if (keycode == KEY_F2 && e->a[0]->power > 2)
		e->a[0]->power--;
}

int			key_hook(int keycode, t_env *e)
{
	key_hook_color(keycode, e);
	key_hook_end(keycode, e);
	key_hook_change(keycode, e);
	key_hook_heads(keycode, e);
	reload_one(e, 0);
	return (0);
}
