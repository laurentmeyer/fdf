/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transforms.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:45:43 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/28 12:50:31 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"
#include "libft.h"
#include <math.h>

void				matrix44f_translation(t_matrix44f *a, float x, float y, float z)
{
	float	m[4][4];

	ft_bzero(&m, sizeof(m));
	m[0][0] = 1;
	m[0][3] = x;
	m[1][1] = 1;
	m[1][3] = y;
	m[2][2] = 1;
	m[2][3] = z;
	m[3][3] = 1;
	axb_matrix44f(a, (t_matrix44f *)(&m));
}

void				matrix44f_scale(t_matrix44f *a, float x, float y, float z)
{
	float	m[4][4];

	ft_bzero(&m, sizeof(m));
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
	m[3][3] = 1;
	axb_matrix44f(a, (t_matrix44f *)(&m));
}

void				matrix44f_rotation_x(t_matrix44f *a, float radians)
{
	float	m[4][4];

	ft_bzero(&m, sizeof(m));
	m[0][0] = 1;
	m[1][1] = cos(radians);
	m[1][2] = -sin(radians);
	m[2][1] = sin(radians);
	m[2][2] = cos(radians);
	m[3][3] = 1;
	axb_matrix44f(a, (t_matrix44f *)(&m));
}

void				matrix44f_rotation_y(t_matrix44f *a, float radians)
{
	float	m[4][4];

	ft_bzero(&m, sizeof(m));
	m[0][0] = cos(radians);
	m[0][2] = sin(radians);
	m[1][1] = 1;
	m[0][2] = -sin(radians);
	m[2][2] = cos(radians);
	m[3][3] = 1;
	axb_matrix44f(a, (t_matrix44f *)(&m));
}

void				matrix44f_rotation_z(t_matrix44f *a, float radians)
{
	float	m[4][4];

	ft_bzero(&m, sizeof(m));
	m[0][0] = cos(radians);
	m[0][1] = -sin(radians);
	m[1][0] = sin(radians);
	m[1][1] = cos(radians);
	m[2][2] = 1;
	m[3][3] = 1;
	axb_matrix44f(a, (t_matrix44f *)(&m));
}
