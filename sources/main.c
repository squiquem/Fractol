/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:07:15 by squiquem          #+#    #+#             */
/*   Updated: 2018/02/24 15:44:19 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ftl.h"

static int	expose_hook(t_env *e)
{
	int j;

	j = -1;
	while (++j < 6)
		reload_one(e, j);
	return (0);
}

int			quit(void)
{
	exit(1);
	return (0);
}

static void	check_param(int ac, char **av, t_img *a)
{
	if (ac == 2 && ft_strcmp("mandelbrot", av[1]) == 0)
		a->fractal = 0;
	else if (ac == 2 && ft_strcmp("julia", av[1]) == 0)
		a->fractal = 1;
	else if (ac == 2 && ft_strcmp("burningship", av[1]) == 0)
		a->fractal = 2;
	else if (ac == 2 && ft_strcmp("tricorn", av[1]) == 0)
		a->fractal = 3;
	else if (ac == 2 && ft_strcmp("newton", av[1]) == 0)
		a->fractal = 4;
	else
		print_error("usage: ./fractol <julia burningship newton "
		"mandelbrot tricorn>");
}

int			main(int ac, char **av)
{
	t_env	*e;
	int		i;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		print_error("Error malloc");
	i = -1;
	while (++i < 6)
		if (!(e->a[i] = (t_img*)malloc(sizeof(t_img))))
			print_error("Error malloc");
	check_param(ac, av, e->a[0]);
	if (!(e->mlx = mlx_init()))
		print_error("Error mlx init");
	if (!(e->win = mlx_new_window(e->mlx, WIN_W, WIN_H, "Fractol squiquem")))
		print_error("Error mlx newwindow");
	e->a[0]->name = av[1];
	init(e);
	display_controls();
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_hook(e->win, 2, 1L << 0, key_hook, e);
	mlx_hook(e->win, 17, 1L << 17, quit, e);
	mlx_hook(e->win, MOTION_NOTIFY, PTR_MOTION_MASK, mouse_move_hook, e);
	mlx_mouse_hook(e->win, mouse_key_hook, e);
	mlx_loop(e->mlx);
	pthread_exit(NULL);
	return (1);
}
