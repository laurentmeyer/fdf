/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:01:23 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/25 21:53:06 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#include <stdio.h>

void	print_point(t_vec4f *pt)
{
	printf("x = %f y = %f z = %f\n", *pt[0], *pt[1], *pt[2]);
}

void	print_points_array(t_data *data, t_vec4f ***array)
{
	int		i;
	int		j;
	t_vec4f	*pt;

	printf("\n-----------------\n");
	i = 0;
	while (i < data->lines)
	{
		j = 0;
		while (j < data->cols)
		{
			pt = array[i][j];
			printf("x = %f y = %f z = %f\n", *pt[0], *pt[1], *pt[2]);
			++j;
		}
		++i;
	}
}

void	update_cam_points(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < data->lines)
	{
		j = 0;
		while (j < data->cols)
		{
			m44f_x_vec4f_to((data->cam_pts)[i][j],
								data->cam->wtoc,
								(data->world_pts)[i][j]);
			++j;
		}
		++i;
	}
}

void	update_camera(t_data *data)
{
	int		i;

	i = -1;
	while (++i < 16)
		(*(data->cam->wtoc))[i / 4][i % 4] = ((i / 4) == (i % 4)) ? 1 : 0;
	matrix44f_translation(data->cam->wtoc, 1.5, 1.0, 1.5);
/* A ADAPTER !!!!!!!*/	
	matrix44f_rotation_z(data->cam->wtoc, data->cam->xy_angle);
	matrix44f_rotation_y(data->cam->wtoc, data->cam->xz_angle);
	update_cam_points(data);
	print_matrix(data->cam->wtoc);
	print_points_array(data, data->world_pts);
}

t_cam			*init_cam(t_data *data)
{
	if ((data->cam = (t_cam *)malloc(sizeof(t_cam))))
	{
		data->cam->xy_angle = 30 * M_PI / 180;
		data->cam->xz_angle = 40 * M_PI / 180;
		data->cam->distance = 50;
		if (!(data->cam->wtoc = matrix44f_identity()))
			return (NULL);
		update_camera(data);
	}
	return (data->cam);
}

t_vec4f				***init_pts_array(t_data *data)
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
			if (!(dest[i][j] = vec4f_new(1, 2, 3, 1)))
				return (NULL);
			++j;
		}
		++i;
	}
	return (dest);
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
				|| !(data->cam_pts = init_pts_array(data))
				|| !(init_cam(data))
				|| !(data->zbuffer = (float *)malloc(data->cols * data->lines
						* sizeof(float)))
		   )
			return (NULL);
	}
	return (data);
}
