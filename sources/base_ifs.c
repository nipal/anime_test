/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_ifs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 05:01:48 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/12 12:33:12 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int						reset_base(t_env *e)
{
	if (e->trans_add != 0 && e->base_add != 0)
		polygone_destroy(&(e->trans_model));
	if (e->base_add != 0 && e->trans_add != 0)
		polygone_destroy(&(e->transform));
	e->base_add = 0;
	e->base_model = e->actif;
	return (1);
}

int						reset_transform(t_env *e)
{
	if (e->trans_add != 0 && e->base_add != 0)
		polygone_destroy(&(e->trans_model));
	if (e->base_add != 0 && e->trans_add != 0)
		polygone_destroy(&(e->transform));
	e->trans_add = 0;
	e->trans_model = e->actif;
	return (1);
}

int						actu_base(t_env *e, t_polygone *src)
{
	polygone_destroy(&(e->base));
	e->base = scale_segment(src, &(e->border_b), &(e->base_cadre), e->tr_base);
	print_fractal(e);
	return (1);
}

int						actu_transform(t_env *e, t_polygone *src)
{
	if (e->moving)
	{
		polygone_destroy(&(e->result_trans_model));
		e->result_trans_model = copy_segment_neutre(src);
		motion_free(&(e->trans_motion));
		e->trans_motion = motion_new_from_polygone(src); 
	}
	else
	{
		polygone_destroy(&(e->transform));
		e->transform = transform(src);
		print_fractal(e);
	}
	return (1);
}

void					redefine_base(t_polygone *new_base, t_border *from
		, t_win *to)
{
	double		coef_x;
	double		coef_y;
	t_polygone	*tmp;

	if (!new_base)
		return ;
	polygone_destroy(&(to->e->base));
	to->e->base = NULL;
	coef_x = (to->size_x) / (from->x1 - from->x0);
	coef_y = (to->size_y) / (from->y1 - from->y0);
	while (new_base)
	{
		tmp = copy_node(new_base, 0);
		tmp->pos->m[0] = (tmp->pos->m[0] - from->x0) * coef_x;
		tmp->pos->m[1] = (tmp->pos->m[1] - from->y0) * coef_y;
		polygone_push_back(&(to->e->base), tmp);
		new_base = new_base->next;
	}
}
