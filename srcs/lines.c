/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:39:28 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/28 20:02:29 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include "fdf.h"
#include <math.h>

#include <stdio.h>

void	trace_v_line(t_data *data, t_vec4f *a, t_vec4f *b, int color)
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

void	trace_line(t_data *data, t_vec4f *a, t_vec4f *b, int color)
{
	float	error;
	float	deltaerr;
	int		x;
	int		y;

	print_point(a);
	print_point(b);
	if ((int)((*a)[0]) == (int)((*b)[0]))
		trace_v_line(data, a, b, color);
	else if ((int)((*a)[0]) > (int)((*b)[0]))
		trace_line(data, b, a, color);
	else
	{
		error = -1.0;
		deltaerr = ((*a)[1] - (*b)[1]) / ((*a)[0] - (*b)[0]);
		printf("delta error = %f\n", deltaerr);
		x = (int)((*a)[0]);
		y = (int)((*a)[1]);
		while (++x < (int)((*b)[0]))
		{
			pixel_put(data, x - 1, y, color);
			error += fabs(deltaerr);
			(error >= 0.0 && deltaerr <= 0) ? ++y : --y;
			error -= (error >= 0.0) ? 1.0 : 0.0;
		}
	}
}
