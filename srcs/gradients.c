/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradients.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 12:48:54 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/03 13:38:40 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include "fdf.h"
#include <math.h>

static void	trace_v_gradient(t_data *data, t_vec4f *a, t_vec4f *b, int pixels)
{
	int		x;
	int		y;
	int		i;

	pixels = distance_pixels(a, b);
	if ((int)((*a)[1]) > (int)((*b)[1]))
		trace_v_gradient(data, b, a, 0);
	else
	{
		x = (int)((*a)[0]);
		y = (int)((*a)[1]);
		i = 0;
		while (y < (int)((*b)[1]))
		{
			pixel_put(data, x, y,
					color_between_ratio(a, b, (float)i++ / (float)pixels));
			++y;
		}
	}
}

static void	trace_small_gradient(t_data *data,
									t_vec4f *a, t_vec4f *b, int pixels)
{
	float	slope;
	float	error;
	int		x;
	int		y;
	int		i;

	pixels = distance_pixels(a, b);
	slope = ((*b)[1] - (*a)[1]) / ((*b)[0] - (*a)[0]);
	error = -1.0;
	x = (int)((*a)[0]);
	y = (int)((*a)[1]);
	i = 0;
	while (x < (int)((*b)[0]))
	{
		pixel_put(data, x, y,
				color_between_ratio(a, b, (float)i++ / (float)pixels));
		error += fabs(slope);
		if (error >= 0.0)
		{
			y += (slope > 0) ? 1 : -1;
			--error;
		}
		++x;
	}
}

static void	trace_big_gradient(t_data *data, t_vec4f *a, t_vec4f *b, int pixels)
{
	float	slope;
	float	error;
	int		x;
	int		y;
	int		i;

	pixels = distance_pixels(a, b);
	slope = ((*b)[1] - (*a)[1]) / ((*b)[0] - (*a)[0]);
	error = -1.0;
	x = (int)((*a)[0]);
	y = (int)((*a)[1]);
	i = 0;
	while (y < (int)((*b)[1]))
	{
		pixel_put(data, x, y, color_between_ratio(a, b,
					(float)i++ / (float)pixels));
		error += fabs(1 / slope);
		if (error >= 0.0)
		{
			x += (slope > 0) ? 1 : -1;
			--error;
		}
		++y;
	}
}

static void	trace_gradient(t_data *data, t_vec4f *a, t_vec4f *b)
{
	if ((int)((*a)[0]) == (int)((*b)[0]))
		trace_v_gradient(data, a, b, 0);
	else if (fabs(((*b)[1] - (*a)[1]) / ((*b)[0] - (*a)[0])) > 1)
		(int)((*a)[1]) < (int)((*b)[1]) ?
			trace_big_gradient(data, a, b, 0)
			: trace_big_gradient(data, b, a, 0);
	else
		(int)((*a)[0]) < (int)((*b)[0]) ?
			trace_small_gradient(data, a, b, 0)
			: trace_small_gradient(data, b, a, 0);
}

void		trace_all_gradients(t_data *data)
{
	int		i;
	int		j;
	t_vec4f	*pt;
	t_vec4f	*next;

	i = 0;
	while (i < data->lines)
	{
		j = 0;
		while ((pt = (data->screen_pts)[i][j])
				&& (next = (data->screen_pts)[i][j++ + 1]))
			trace_gradient(data, pt, next);
		++i;
	}
	i = 0;
	while (i < data->lines - 1)
	{
		j = 0;
		while ((pt = (data->screen_pts)[i][j])
				&& (next = (data->screen_pts)[i + 1][j++]))
			trace_gradient(data, pt, next);
		++i;
	}
}
