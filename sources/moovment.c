/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moovment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 07:56:20 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/12 12:35:59 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fractol.h"

/*
	La on a juste une position qui commence a zero et on ajoute a la position de l'objet
	A chaque toure de boucle on vs incrementer les position des truc machin
	si non on va juste les re cree quand il le sont (changement d'origine, ajout, suppresion)

	quand l'option est ecctiver a chaque tours de boucle on active t on voila	
	il faut init un truc neutre au re update des
*/

t_motion	*motion_new()
{
	t_motion	*new;

	if (!(new = (t_motion*)malloc(sizeof(t_motion))))
		return (NULL);
	ft_bzero(new, sizeof(t_motion));
	return (new);
}

t_motion	*motion_new_from_polygone(t_polygone *begin)
{
	t_motion	*motion_begin;
	t_motion	*motion;
	t_motion	*prev;

	prev = NULL;
	while (begin)
	{
		if (!(motion = motion_new()))
			return (NULL);
		if (prev)
			prev->next = motion;
		else
			motion_begin = motion;
		prev = motion;
		begin = begin->next;
	}
	return (motion_begin);
}

int		motion_free(t_motion **begin)
{
	t_motion	*node;
	t_motion	*tmp;

	if (!begin || !*begin)
		return (1);
	node = *begin;
	while (node)
	{
		tmp = node->next;
		free(node);
		node = tmp;
	}
	*begin = NULL;
	return (1);
}

void	motion_walker(t_motion *obj, double friction, double increm)
{
	double	r;
	double	upx;
	double	upy;
	double	fx;
	double	fy;


	r = ((double)rand() / (double)RAND_MAX);
	if (r < 0.25)
		obj->vx += increm;
	else if (r < 0.5)
		obj->vx -= increm;
	else if (r < 0.75)
		obj->vy += increm;
	else
		obj->vy -= increm;
	upx = obj->px / SIZE;
	upy = obj->py / SIZE;
	fx = friction * (1 - fabs(upx));
	fy = friction * (1 - fabs(upy));
	obj->vx = (obj->vx) * fx;
	obj->vy = (obj->vy) * fy;
	obj->vx -= upx;
	obj->vy -= upy;
	obj->px += obj->vx;
	obj->py += obj->vy;
}

int						actu_transform_v2(t_env *e, t_polygone *src)
{
	polygone_destroy(&(e->transform));
	e->transform = transform(src);
	print_fractal(e);
	return (1);
}

t_polygone		*copy_segment_neutre(t_polygone *src)
{
	t_polygone	*new_beg;
	double		pos[3] = {0, 0, 0};

	new_beg = NULL;
	while (src)
	{
		polygone_push_back(&new_beg, creat_node(0, pos, pos));
		src = src->next;
	}
	return (new_beg);
}

void	actu_motion(t_win *w, t_motion *motion, t_polygone *trans, t_polygone *result)
{
	double	dist;

	while (trans && motion && result)
	{
		result->pos->m[0] = trans->pos->m[0] + motion->px;
		result->pos->m[1] = trans->pos->m[1] + motion->px;
		dist = (w->mouse->m[0] - result->pos->m[0]) * (w->mouse->m[0] - result->pos->m[0]); 
		dist += (w->mouse->m[1] - result->pos->m[1]) * (w->mouse->m[1] - result->pos->m[1]); 
		dist = sqrt(dist);
		if (dist > w->e->r_select)
			motion_walker(motion, FRICTION, INCR_WALKER);
		result = result->next;	
		trans = trans->next;
		motion = motion->next;
	}
	if (trans || motion || result)
	{
		ft_putstr("someone is too small\n");
		if (trans)
			ft_putstr("trans steel here\n");
		if (motion)
			ft_putstr("motion steel here\n");
		if (result)
			ft_putstr("result steel here\n");
	}
	actu_transform_v2(w->e, result);
}
