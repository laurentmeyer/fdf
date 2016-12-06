/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 17:04:00 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/03 16:32:37 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include "libft.h"
#include "fdf.h"
#include <stdlib.h>

t_vec4f				*vec4f_new(float x, float y, float z, float w)
{
	float		v[4];

	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
	return (vec4f_dup((t_vec4f *)(&v)));
}

t_vec4f				*vec4f_dup(t_vec4f *v)
{
	t_vec4f		*tmp;

	if (!v || !(*v))
		return (NULL);
	if ((tmp = (t_vec4f *)malloc(sizeof(t_vec4f))))
		ft_memcpy(tmp, v, sizeof(t_vec4f));
	return (tmp);
}

void				m44f_x_vec4f(t_matrix44f *m, t_vec4f *v)
{
	float		tmp[4];
	int			i;

	ft_memcpy(&tmp, v, sizeof(tmp));
	i = 0;
	while (i < 4)
	{
		(*v)[i] = (*m)[i][0] * tmp[0]
					+ (*m)[i][1] * tmp[1]
					+ (*m)[i][2] * tmp[2]
					+ (*m)[i][3] * tmp[3];
		++i;
	}
}

void				m44f_x_vec4f_to(t_vec4f *dest, t_matrix44f *m, t_vec4f *v)
{
	int			i;

	i = 0;
	while (i < 4)
	{
		(*dest)[i] = (*m)[i][0] * (*v)[0]
					+ (*m)[i][1] * (*v)[1]
					+ (*m)[i][2] * (*v)[2]
					+ (*m)[i][3] * (*v)[3];
		++i;
	}
}
