/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:01:23 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/29 11:46:41 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#include <stdio.h>


t_cam			*init_cam(t_data *data)
{
	if ((data->cam = (t_cam *)malloc(sizeof(t_cam))))
	{
		data->cam->xy_angle = INIT_XY * M_PI / 180;
		data->cam->xz_angle = INIT_XZ * M_PI / 180;
		data->cam->distance = 2;
		data->cam->znear = 1.0;
		data->cam->zfar = 1000.0;
		if (!(data->cam->wtoc = matrix44f_identity())
				|| !(data->cam->perspect_proj = matrix44f_identity())
				|| !(data->cam->ortho_proj = matrix44f_identity()))
			return (NULL);
		update_camera(data);
	}
	return (data->cam);
}

t_vec4f			***init_pts_array(t_data *data)
{
	int		i;
	int		j;
	t_vec4f	***dest;

	if (!(dest = (t_vec4f ***)malloc(data->lines * sizeof(t_vec4f **))))
		return (NULL);
	i = 0;
	while (i < data->lines)
	{
		if (!(dest[i] = (t_vec4f **)malloc(data->cols * sizeof(t_vec4f *))))
			return (NULL);
		j = 0;
		while (j < data->cols)
		{
			if (!(dest[i][j] = vec4f_new(0, 0, 0, 1)))
				return (NULL);
			++j;
		}
		++i;
	}
	return (dest);
}

int					center_pts_array(t_data *data)
{
	int		i;
	int		j;
	t_vec4f	*pt;

	i = 0;
	while (i < data->lines)
	{
		j = 0;
		while (j < data->cols)
		{
			(pt = (data->world_pts)[i][j]);
			(*pt)[0] -= (float)(data->cols - 1.0) / 2.0;
			(*pt)[2] -= (float)(data->lines - 1.0) / 2.0;
			++j;
		}
		++i;
	}
	return (1);
}


t_data				*init_data(void)
{
	t_data	*data;

	if ((data = (t_data *)malloc(sizeof(t_data))))
	{
		if (!(data->ptr = mlx_init())
				|| !(data->win = mlx_new_window(data->ptr, WIN_W, WIN_H, WIN_T))
				|| !(data->img_ptr = mlx_new_image(data->ptr, WIN_W, WIN_H))
				|| !(data->img_addr = mlx_get_data_addr(data->img_ptr,
						&(data->bits_per_pixel),
						&(data->size_line),
						&(data->endian)))
				|| !(data->cols = 2)
				|| !(data->lines = 2)
				|| !(data->world_pts = init_pts_array(data))
				|| !((data->world_pts)[0][0] = vec4f_new(0.0, 0.0, 0.0, 1.0))
				|| !((data->world_pts)[0][1] = vec4f_new(1.0, 0.0, 0.0, 1.0))
				|| !((data->world_pts)[1][0] = vec4f_new(0.0, 1.0, 0.0, 1.0))
				|| !((data->world_pts)[1][1] = vec4f_new(0.0, 0.0, 1.0, 1.0))
				|| !(center_pts_array(data))
				|| !(data->cam_pts = init_pts_array(data))
				|| !(data->screen_pts = init_pts_array(data))
				|| !(init_cam(data))
				|| !(data->zbuffer = (float *)malloc(data->cols * data->lines
						* sizeof(float)))
		   )
			return (NULL);
	}
	return (data);
}
