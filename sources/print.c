/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 02:37:07 by squiquem          #+#    #+#             */
/*   Updated: 2018/02/24 15:46:40 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftl.h"

void		print_error(char *cause)
{
	ft_putendl_fd(cause, 2);
	exit(1);
}

void		display_controls(void)
{
	ft_putstr("\
____________________________\n\
CONTROLS:\n\
Translation:\n\
	Y: Key: UP, DOWN\n\
	X: Key: LEFT, RIGHT\n\
Iterations:\n\
	x2: +	/2: -\n\
Change color:\n\
	Keypad:	0->9\n\
	Smooth:	DELETE\n\
	Cycles:	SUPPR\n\
	Sharp:	PGUP, PGDOWN \n\
	Heads:	F1-F2\n\
Restart:\n\
	ENTER\n\
Block Julia parameter:\n\
	SPACE\n\
Zoom:\n\
	IN & OUT: mouse wheel or click\n\
Infos:\n\
	F12\n\
____________________________\n\
");
}

static void	put_info_julia(t_env *e, char *b[6])
{
	int	i;

	i = 193;
	mlx_string_put(e->mlx, e->win, 3, 39, 0xff0000, "Julia parameter = (");
	if (e->a[0]->mouse->x < 0)
	{
		mlx_string_put(e->mlx, e->win, i, 39, 0xff0000, "-");
		i += 10;
	}
	mlx_string_put(e->mlx, e->win, i, 39, 0xff0000, b[2]);
	mlx_string_put(e->mlx, e->win, i + 10, 39, 0xff0000, ".");
	mlx_string_put(e->mlx, e->win, i + 20, 39, 0xff0000, b[3]);
	mlx_string_put(e->mlx, e->win, i + 40, 39, 0xff0000, ", ");
	if (e->a[0]->mouse->y < 0)
	{
		mlx_string_put(e->mlx, e->win, i + 60, 39, 0xff0000, "-");
		i += 10;
	}
	mlx_string_put(e->mlx, e->win, i + 60, 39, 0xff0000, b[4]);
	mlx_string_put(e->mlx, e->win, i + 70, 39, 0xff0000, ".");
	mlx_string_put(e->mlx, e->win, i + 80, 39, 0xff0000, b[5]);
	mlx_string_put(e->mlx, e->win, i + 100, 39, 0xff0000, ")");
}

void		put_info(t_env *e)
{
	char	*b[6];
	int		i;

	b[0] = ft_itoa(e->a[0]->max_iter);
	b[1] = ft_ltoa(e->a[0]->zoom / SCALE);
	b[2] = ft_itoa((int)ABS(e->a[0]->mouse->x));
	b[3] = ft_itoa((int)ABS(e->a[0]->mouse->x * 100) % 100);
	b[4] = ft_itoa((int)ABS(e->a[0]->mouse->y));
	b[5] = ft_itoa((int)ABS(e->a[0]->mouse->y * 100) % 100);
	mlx_string_put(e->mlx, e->win, 3, 0, 0xff0000, e->a[0]->name);
	mlx_string_put(e->mlx, e->win, 3, 13, 0xff0000, "Iterations = ");
	mlx_string_put(e->mlx, e->win, 133, 13, 0xff0000, b[0]);
	mlx_string_put(e->mlx, e->win, 3, 26, 0xff0000, "zoom = x");
	mlx_string_put(e->mlx, e->win, 83, 26, 0xff0000, b[1]);
	if (e->a[0]->fractal == 1)
		put_info_julia(e, b);
	i = -1;
	while (++i < 6)
		free(b[i]);
}
