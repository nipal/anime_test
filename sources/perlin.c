/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 03:19:59 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/12 03:34:06 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   1073741824	=>	2^30
**
**   nombre premier:
**   15731
**   789221
**   1376312589
*/


//Fournit une valeur aléatoire entre -1 et 1
double rand_noise(int t)
{
	t = (t<<13) ^ t;
	t = (t * (t * t * 15731 + 789221) + 1376312589);
	return 1.0 - (t & 0x7fffffff) / 1073741824.0;
}
//On pourra obtenir une valeur entre 0 et 1 en utilisant
////la formule : (rand_noise(t) + 1.) / 2.



double noise_2d(int x, int y)
{
	int tmp = rand_noise(x) * 850000;
	return rand_noise(tmp + y);
}


double noise_nd(int *data_set, int dim)
{
	int i;
	double r = 0.;

	for(i = 0; i < dim; i++)
		r = rand_noise(data_set[i] + (int)(r * 850000));
	return r;
}

