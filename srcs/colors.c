/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 13:18:15 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/03 18:31:20 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	decomp_color(int color, int buffer[3])
{
	buffer[2] = color & 0xFF;
	color = color >> 8;
	buffer[1] = color & 0xFF;
	color = color >> 8;
	buffer[0] = color & 0xFF;
}

int		clerp(int ca, int cb, float ratio)
{
	int	adecomp[3];
	int	bdecomp[3];
	int	result[3];
	int	res;
	int	i;

	decomp_color(ca, adecomp);
	decomp_color(cb, bdecomp);
	i = -1;
	while (++i < 3)
		result[i] = adecomp[i] + (int)(ratio * (bdecomp[i] - adecomp[i]));
	res = result[0];
	res = res << 8;
	res += result[1];
	res = res << 8;
	res += result[2];
	return (res);
}

int		color_between_ratio(t_vec4f *a, t_vec4f *b, float r)
{
	int	adecomp[3];
	int	bdecomp[3];
	int	result[3];
	int	res;
	int	i;

	if (distance_pixels(a, b) == 0)
		return ((*a)[2]);
	decomp_color((*a)[2], adecomp);
	decomp_color((*b)[2], bdecomp);
	i = -1;
	while (++i < 3)
		result[i] = adecomp[i] + (int)((float)(bdecomp[i] - adecomp[i]) * r);
	res = result[0];
	res = res << 8;
	res += result[1];
	res = res << 8;
	res += result[2];
	return (res);
}

int		color_for_height(t_data *data, float min_y, float max_y, float height)
{
	if (min_y == max_y)
		return (data->max_col);
	return (clerp(data->min_col, data->max_col,
				(height - min_y) / (max_y - min_y)));
}
