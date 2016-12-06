/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:39:28 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/03 13:33:36 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include "fdf.h"
#include <math.h>

#include <stdio.h>

static void	trace_v_line(t_data *data, t_vec4f *a, t_vec4f *b, int color)
{
	int x;
	int	y;

	if ((int)((*a)[1]) > (int)((*b)[1]))
		trace_v_line(data, b, a, color);
	else
	{
		x = (int)((*a)[0]);
		y = (int)((*a)[1]);
		while (y < (int)((*b)[1]))
			pixel_put(data, x, y++, color);
	}
}

static void	trace_small_slope(t_data *data, t_vec4f *a, t_vec4f *b, int color)
{
	float	slope;
	float	error;
	int		x;
	int		y;

	slope = ((*b)[1] - (*a)[1]) / ((*b)[0] - (*a)[0]);
	error = -1.0;
	x = (int)((*a)[0]);
	y = (int)((*a)[1]);
	while (x < (int)((*b)[0]))
	{
		pixel_put(data, x, y, color);
		error += fabs(slope);
		if (error >= 0.0)
		{
			y += (slope > 0) ? 1 : -1;
			--error;
		}
		++x;
	}
}

static void	trace_big_slope(t_data *data, t_vec4f *a, t_vec4f *b, int color)
{
	float	slope;
	float	error;
	int		x;
	int		y;

	slope = ((*b)[1] - (*a)[1]) / ((*b)[0] - (*a)[0]);
	error = -1.0;
	x = (int)((*a)[0]);
	y = (int)((*a)[1]);
	while (y < (int)((*b)[1]))
	{
		pixel_put(data, x, y, color);
		error += fabs(1 / slope);
		if (error >= 0.0)
		{
			x += (slope > 0) ? 1 : -1;
			--error;
		}
		++y;
	}
}

void		trace_line(t_data *data, t_vec4f *a, t_vec4f *b, int color)
{
	if ((int)((*a)[0]) == (int)((*b)[0]))
		trace_v_line(data, a, b, color);
	else if (fabs(((*b)[1] - (*a)[1]) / ((*b)[0] - (*a)[0])) > 1)
		(int)((*a)[1]) < (int)((*b)[1]) ?
			trace_big_slope(data, a, b, color)
			: trace_big_slope(data, b, a, color);
	else
		(int)((*a)[0]) < (int)((*b)[0]) ?
			trace_small_slope(data, a, b, color)
			: trace_small_slope(data, b, a, color);
}
