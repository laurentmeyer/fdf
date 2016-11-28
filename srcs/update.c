/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 17:46:31 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/28 19:25:03 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "matrices.h"
#include <stdio.h>
#include <stdlib.h>

void	put_grid(t_data *data, int step);

void	update_screen_points(t_data *data)
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
			pt = (data->screen_pts)[i][j];
			m44f_x_vec4f_to(pt,
								data->cam->ortho_proj,
								(data->cam_pts)[i][j]);
			(*pt)[0] = WIN_W * (((*pt)[0] + 1) / 2);
			(*pt)[1] = WIN_H * (((*pt)[1] + 1) / 2);
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
/* A ADAPTER !!!!!!!*/	
	matrix44f_rotation_z(data->cam->wtoc, data->cam->xy_angle);
	matrix44f_rotation_y(data->cam->wtoc, data->cam->xz_angle);
	matrix44f_translation(data->cam->wtoc,
							1.0 * data->cam->distance + (WIN_W - 1) / 2,
							1.0 * data->cam->distance,
							1.0 * data->cam->distance + (WIN_H - 1) / 2);
	update_cam_points(data);
	update_proj_orth_matrix(data);
	update_proj_perspect_matrix(data);
	update_screen_points(data);
	ft_bzero(data->img_addr, data->bits_per_pixel * WIN_W * WIN_H / 8);
	put_grid(data, 50);
	put_all_points(data);
	trace_line(data, (data->screen_pts)[0][0], (data->screen_pts)[0][1], RED);
	trace_line(data, (data->screen_pts)[0][0], (data->screen_pts)[1][0], GREEN);
	trace_line(data, (data->screen_pts)[0][0], (data->screen_pts)[1][1], BLUE);
	if (!mlx_put_image_to_window(data->ptr, data->win, data->img_ptr, 0, 0))
		exit(0);


	print_matrix(data->cam->wtoc);
	printf("\n-----WORLD POINTS-----\n");
	print_points_array(data, data->world_pts);
	printf("\n-----CAMERA POINTS-----\n");
	print_points_array(data, data->cam_pts);


	printf("\n-----SCREEN POINTS-----\n");
	print_points_array(data, data->screen_pts);
}


