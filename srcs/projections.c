/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 10:32:14 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/03 15:24:18 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <math.h>

void				update_proj_orth_matrix(t_data *data)
{
	t_matrix44f	*a;
	float		fovx;
	float		fovy;

	fovx = 2 * 180 / M_PI * atan(WIN_W / data->cam->znear);
	fovy = 2 * 180 / M_PI * atan(WIN_H / data->cam->znear);
	a = data->cam->ortho_proj;
	ft_bzero(a, sizeof(t_matrix44f));
	(*a)[0][0] = atan(fovx / 2);
	(*a)[1][1] = atan(fovy / 2);
	(*a)[2][2] = -2 / (data->cam->zfar - data->cam->znear);
	(*a)[2][3] = -(data->cam->zfar + data->cam->znear)
						/ (data->cam->zfar - data->cam->znear);
	(*a)[3][3] = 1;
}
