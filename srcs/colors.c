/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 13:18:15 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/02 21:02:46 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#define MIN_COLOR 0xFF0000
#define MAX_COLOR 0x0000FF

int		iabs(int a)
{
	return (a < 0 ? -a : a);
}

int		distance_pixels(t_vec4f *a, t_vec4f *b)
{
	return (iabs((*b)[0] - (*a)[0]) + iabs((*b)[1] - (*a)[1]));
}

float	distance_coords(int ax, int ay, int bx, int by)
{
	return (sqrt((ax - ay) * (ax - ay) + (bx - by) * (bx - by)));
}

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

	if (distance_coords((*a)[0], (*a)[1], (*b)[0], (*b)[1]) == 0.0)
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

//int		color_between_pts(t_vec4f *a, t_vec4f *b, int x, int y)
//{
//	int	adecomp[3];
//	int	bdecomp[3];
//	int	result[3];
//	int	res;
//	int	i;
//
//	if (distance_coords((*a)[0], (*a)[1], (*b)[0], (*b)[1]) == 0.0)
//		return ((*a)[2]);
//	decomp_color((*a)[2], adecomp);
//	decomp_color((*b)[2], bdecomp);
//	i = -1;
//	while (++i < 3)
//		result[i] = adecomp[i] + (int)((float)(bdecomp[i] - adecomp[i])
//				* distance_coords((*a)[0], (*a)[1], x, y)
//				/ distance_coords((*a)[0], (*a)[1], (*b)[0], (*b)[1]));
//	res = result[0];
//	res = res << 8;
//	res += result[1];
//	res = res << 8;
//	res += result[2];
////	print_point(a);
////	print_point(b);
////	printf("color between : %x\n", res);
//	return (res);
//}

//void	get_clerp_unit(int ca, int cb, int units, float buffer[3])
//{
//	int	adecomp[3];
//	int	bdecomp[3];
//	int	i;
//
//	decomp_color(ca, adecomp);
//	decomp_color(cb, bdecomp);
//	i = -1;
//	while (++i < 3)
//		buffer[i] = (float)adecomp[i]
//			+ ((float)(bdecomp[i] - adecomp[i]) / units);
//}
//
//int		add_clerp_units(int color, float clerp[3], int units)
//{
//	int		decomp[3];
//	int		result[3];
//	int		res;
//	int 	i;
//
//	decomp_color(color, decomp);
//	i = -1;
//	while (++i < 3)
//		result[i] = (int)(decomp[i] + (float)units * clerp[i]);
//	res = result[0];
//	res = res << 8;
//	res += result[1];
//	res = res << 8;
//	res += result[2];
//	return (res);
//}

int		color_for_height(float min_y, float max_y, float height)
{
	if (min_y == max_y)
		return (MAX_COLOR);
	return (clerp(MIN_COLOR, MAX_COLOR, (height - min_y) / (max_y - min_y)));
}
