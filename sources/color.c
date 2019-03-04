/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:43:24 by squiquem          #+#    #+#             */
/*   Updated: 2018/02/20 20:10:26 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftl.h"

static t_color	clerp(t_color c1, t_color c2, double p)
{
	t_color c;

	if (c1.value == c2.value)
		return (c1);
	c.rgba.r = (unsigned char)ft_lerpi((int)c1.rgba.r, (int)c2.rgba.r, p);
	c.rgba.g = (unsigned char)ft_lerpi((int)c1.rgba.g, (int)c2.rgba.g, p);
	c.rgba.b = (unsigned char)ft_lerpi((int)c1.rgba.b, (int)c2.rgba.b, p);
	c.rgba.a = (unsigned char)0x00;
	return (c);
}

static t_color	linear_color(double i, int max, t_palette *p)
{
	double		index;
	double		adjust;
	int			c;

	if (p->cycle)
		index = fmod(i, p->cycle - 1) / (p->cycle - 1);
	else
		index = i / max;
	c = p->count - 1;
	adjust = fmod(index, 1.0f / c) * c;
	return (clerp((t_color)(p->colors[(int)(index * c) + 1]),
		(t_color)(p->colors[(int)(index * c)]),
		(int)(adjust + 1) - adjust));
}

static t_color	smooth_color(t_iter p, int max, t_palette *pal, int k)
{
	double i;
	double zn;
	double nu;

	zn = log(p.zn.x * p.zn.x + p.zn.y * p.zn.y) / 2.0f;
	nu = log(zn / log(k)) / log(k);
	i = p.i + 1 - nu;
	if (i < 0)
		i = 0;
	return (linear_color(i, max, pal));
}

int				get_color(t_img *e, t_iter p)
{
	if (p.i >= e->max_iter)
		return (0);
	if (e->smooth)
		return (smooth_color(p, e->max_iter, e->palette, e->power).value);
	return (linear_color((double)p.i, e->max_iter, e->palette).value);
}

t_palette		*get_palette(void)
{
	static t_palette	array[11];

	array[0] = (t_palette){1, 0, {0xffffff}};
	array[1] =
		(t_palette){5, 0, {0x7f1637, 0x047878, 0xffb733, 0xf57336, 0xc22121}};
	array[2] =
		(t_palette){5, 0, {0x0d1c33, 0x17373c, 0x2b6832, 0x4f9300, 0xa1d700}};
	array[3] =
		(t_palette){5, 0, {0x002f2f, 0x046380, 0xefecca, 0xa7a37e, 0xe6e2af}};
	array[4] =
		(t_palette){4, 0, {0xee1100, 0xffffaa, 0xaa2222, 0xff8000}};
	array[5] =
		(t_palette){5, 0, {0x00cc00, 0x2211ff, 0x000099, 0x99ffff, 0x0099ff}};
	array[6] =
		(t_palette){5, 0, {0xff7eab, 0xff9791, 0xffac7d, 0xffb77b, 0xffd77a}};
	array[7] =
		(t_palette){5, 10, {0x404040, 0x808080, 0xc0c0c0, 0xffffff, 0x404040}};
	array[8] = (t_palette){16, 50, {0xffffff, 0xc0c0c0, 0x000000, \
		0xff0000, 0xe35f14, 0xffff00, 0x808000, 0x00ff00, 0x008000, 0x00ffff, \
		0x008080, 0x0000ff, 0x000080, 0xff00ff, 0x800080, 0xffffff}};
	array[9] = (t_palette){16, 16, {0x421e15, 0x19071a, 0x09012f, 0x040449, \
		0x000764, 0x0c2c8a, 0x1852b1, 0x397dd1, 0x86b5e5, 0xd3ecf8, 0xf1e9bf, \
		0xf8c95f, 0xffaa00, 0xcc8000, 0x995700, 0x421e15}};
	array[10] = (t_palette){0, 0, {0}};
	return (array);
}
