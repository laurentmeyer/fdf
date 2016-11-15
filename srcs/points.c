/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 18:20:56 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/15 19:09:38 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

int		distance(t_pt *a, t_pt *b)
{
	return (lround(sqrt((a->x - b->x) * (a->x - b->x)
					+ (a->y - b->y) * (a->y - b->y)
					+ (a->z - b->z) * (a->y - b->z))));
}

t_pt	*init_point(int x, int y, int z)
{
	t_pt	*pt;

	if ((pt = (t_pt *)malloc(sizeof(t_pt))))
	{
		pt->x = x;
		pt->y = y;
		pt->z = z;
		pt->w = 1;
	}
	return (pt);
}
