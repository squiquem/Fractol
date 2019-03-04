/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:09:49 by squiquem          #+#    #+#             */
/*   Updated: 2018/02/24 16:04:19 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTL_H
# define FTL_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <pthread.h>

# define WIN_H 720
# define WIN_W 1280
# define IMG_W (4 * WIN_W / 5)
# define IMG_H 720
# define SCALE 200
# define MAX_ITER 32
# define NB_FRACTALS 5
# define NB_THR 8

# define MOVE 100
# define ZOOM_IN 1.2
# define ZOOM_OUT 0.8

# define KEY_MOUSE_CLIC_L 1
# define KEY_MOUSE_CLIC_R 2
# define MOUSE_ZOOM_IN 4
# define MOUSE_ZOOM_OUT 5
# define KEY_MOUSE_LEFT 7
# define KEY_MOUSE_RIGHT 6
# define KEY_MOUSE_STOP 49

# define KEY_ESC 53
# define KEY_ENTER 36
# define KEY_DELETE 51
# define KEY_SUPPR 117
# define KEY_F1 122
# define KEY_F2 120
# define KEY_F12 111
# define KEY_SPACE 49
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEYPAD_0 82
# define KEYPAD_1 83
# define KEYPAD_2 84
# define KEYPAD_3 85
# define KEYPAD_4 86
# define KEYPAD_5 87
# define KEYPAD_6 88
# define KEYPAD_7 89
# define KEYPAD_8 91
# define KEYPAD_9 92
# define KEYPAD_PLUS 69
# define KEYPAD_MINUS 78
# define PTR_MOTION_MASK (1L << 6)
# define MOTION_NOTIFY 6

# define KEY_PAGE_UP 116
# define KEY_PAGE_DOWN 121

typedef struct		s_pointi
{
	int				x;
	int				y;
}					t_pointi;

typedef struct		s_pointd
{
	double			x;
	double			y;
}					t_pointd;

typedef struct		s_iter
{
	int				i;
	t_pointd		zn;
}					t_iter;

typedef struct		s_rgba
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}					t_rgba;

typedef union		u_color
{
	int				value;
	t_rgba			rgba;
}					t_color;

typedef struct		s_palette
{
	unsigned char	count;
	int				cycle;
	int				colors[16];
}					t_palette;

typedef struct		s_img
{
	void			*img;
	char			*pixel_img;
	int				bpp;
	int				s_line;
	int				ed;
	int				smooth;
	int				fractal;
	int				sharp;
	int				power;
	long			zoom;
	long			max_iter;
	char			*name;
	t_pointd		*sizeimg;
	t_pointd		*posimg;
	t_pointd		*center;
	t_pointd		*mouse;
	t_palette		*palette;
	pthread_t		thr[NB_THR];
}					t_img;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	t_img			*a[6];
	int				mouse_stop;
	int				info;
}					t_env;

t_iter				mandelbrot(t_pointi *z, t_img *a);
t_iter				julia(t_pointi *w, t_img *a);
t_iter				burningship(t_pointi *z, t_img *e);
t_iter				tricorn(t_pointi *z, t_img *a);
t_iter				newton(t_pointi *z, t_img *e);

int					key_hook(int keycode, t_env *e);
int					mouse_move_hook(int x, int y, t_env *e);
int					mouse_key_hook(int k, int x, int y, t_env *e);

void				reload_one(t_env *e, int j);

int					get_color(t_img *e, t_iter p);
t_palette			*get_palette(void);

t_pointd			*create_point(double x, double y);
void				init(t_env *e);

void				print_error(char *cause);
void				display_controls(void);
void				put_info(t_env *e);

t_pointd			ft_cmul(t_pointd a, t_pointd b);
t_pointd			ft_cpow(t_pointd a, int p);
t_pointd			ft_conj(t_pointd a);
t_pointd			ft_cdiv(t_pointd a, t_pointd b);

#endif
