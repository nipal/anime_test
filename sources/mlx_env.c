/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 04:08:06 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/10 07:32:51 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fractol.h"
#include <stdio.h>

/*
** 	ici il faudrait stoquer les dimetion maximale de la map
** 	on a deja le max x et y il maque le max et le min en z
*/

double		**init_tab_d(int size_x, int size_y)
{
	int		j;
	double	**tab;

	if (!(tab = (double**)malloc(sizeof(double*) * size_y)))
		return (NULL);
	j = 0;
	while (j < size_y)
	{
		if (!(tab[j] = (double*)malloc(sizeof(double) * size_x)))
			return (NULL);
		j++;
	}
	return (tab);
}

void		env_end(t_env *e)
{
	e->y_maxl = SIZE_Y;
	e->x_maxl = SIZE_X;
	e->y_maxh = 2 * SIZE_Y;
	e->x_maxh = 2 * SIZE_X;
	e->zoom = ZOOM;
	e->zoom_on = 0;
	e->zoom_y = 0;
	e->zoom_x = 0;
	e->zoom_finished = 1;
	e->base_add = 0;
	e->trans_add = 0;
	mlx_loop_hook(e->mlx, main_work, e);
	init_koch(e);
	init_the_sliders(e->param, &(e->border_b));
	init_statment(e);
	mlx_loop(e->mlx);
	mlx_do_sync(e->mlx);
}

void		init_win_event(t_win *w, t_env *e)
{
	(void)e;
	mlx_hook(w->win, KEY_PRESS, (1 << 24) - 1, press_key, w);
	mlx_hook(w->win, KEY_RELEASE, (1 << 24) - 1, release_key, w);
	mlx_hook(w->win, BUTTON_PRESS, (1 << 24) - 1, press_button, w);
	mlx_hook(w->win, BUTTON_RELEASE, (1 << 24) - 1, release_button, w);
	mlx_hook(w->win, MOTION_NOTIFY, (1 << 24) - 1, motion_cursor, w);
}

void		init_border_totranslate(t_border *b, t_win *w, double *pt_translate)
{
	b->x0 = 0;
	b->y0 = 0;
	b->x1 = w->size_x;
	b->y1 = w->size_y;
	pt_translate[0] = 0;
	pt_translate[1] = 0;
}

void		env(t_env *e)
{
	if (!e || !(e->mlx = mlx_init()))
		return ;
	if (!(e->fractal = window_init(e, SIZE_KOCH_X, SIZE_KOCH_Y, "fractal"))
		|| !(e->param = window_init(e, SIZE_PARAM_X, SIZE_PARAM_Y, "param")))
		return ;
	init_win_event(e->fractal, e);
	init_win_event(e->param, e);
	init_koch_param_border(e, e->param);
	init_border_totranslate(&(e->base_cadre), e->fractal, e->tr_base);
	env_end(e);
	return ;
}
