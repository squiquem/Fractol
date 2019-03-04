/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 02:02:00 by squiquem          #+#    #+#             */
/*   Updated: 2018/02/24 15:41:53 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftl.h"

t_pointd	ft_cmul(t_pointd a, t_pointd b)
{
	t_pointd	res;

	res.x = a.x * b.x - a.y * b.y;
	res.y = a.x * b.y + a.y * b.x;
	return (res);
}

t_pointd	ft_cpow(t_pointd a, int p)
{
	int			i;
	t_pointd	res;

	res = a;
	i = 0;
	while (++i < p)
		res = ft_cmul(res, a);
	return (res);
}

t_pointd	ft_conj(t_pointd a)
{
	t_pointd	b;

	b.x = a.x;
	b.y = -a.y;
	return (b);
}

t_pointd	ft_cdiv(t_pointd a, t_pointd b)
{
	t_pointd	c;

	if (b.x != 0 || b.y != 0)
	{
		c = ft_cmul(a, ft_conj(b));
		c.x /= (b.x * b.x + b.y * b.y);
		c.y /= (b.x * b.x + b.y * b.y);
	}
	else
	{
		c.x = 0;
		c.y = 0;
	}
	return (c);
}
