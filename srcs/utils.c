/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 12:40:30 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/03 13:46:22 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include "fdf.h"
#include <math.h>

int		iabs(int a)
{
	return (a < 0 ? -a : a);
}

int		distance_pixels(t_vec4f *a, t_vec4f *b)
{
	return (iabs((*b)[0] - (*a)[0]) + iabs((*b)[1] - (*a)[1]));
}

int		center_pts_array(t_data *data)
{
	int		i;
	int		j;
	t_vec4f	*pt;

	i = 0;
	while (i < data->lines)
	{
		j = 0;
		while ((pt = (data->world_pts)[i][j++]))
		{
			(*pt)[0] -= (float)(data->cols - 1.0) / 2.0;
			(*pt)[2] -= (float)(data->lines - 1.0) / 2.0;
		}
		++i;
	}
	return (1);
}
