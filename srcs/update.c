/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 17:46:31 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/29 17:43:30 by lmeyer           ###   ########.fr       */
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
//			(*pt)[0] = WIN_W * (((*pt)[0] + 1) / 2);
//			(*pt)[1] = WIN_H * (((*pt)[1] + 1) / 2);
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
//	t_vec4f	*p1;
//	t_vec4f	*p2;
//	t_vec4f	*p3;
//	t_vec4f	*p4;
//	t_vec4f	*p5;
//	t_vec4f	*p6;
//	t_vec4f	*p7;
//	t_vec4f	*p8;
//	t_vec4f	*p9;
//	t_vec4f	*p10;
//	t_vec4f	*p11;
//	t_vec4f	*p12;

	i = -1;
	while (++i < 16)
		(*(data->cam->wtoc))[i / 4][i % 4] = ((i / 4) == (i % 4)) ? 1 : 0;
/* A ADAPTER !!!!!!!*/	
	matrix44f_rotation_z(data->cam->wtoc, data->cam->xy_angle);
	matrix44f_rotation_y(data->cam->wtoc, data->cam->xz_angle);
	matrix44f_scale(data->cam->wtoc, 30.0, 30.0, 30.0);
	matrix44f_translation(data->cam->wtoc,
							1.0 * data->cam->distance,
							1.0 * data->cam->distance,
							1.0 * data->cam->distance);
//							1.0 * data->cam->distance + (WIN_W - 1) / 2,
//							1.0 * data->cam->distance,
//							1.0 * data->cam->distance + (WIN_H - 1) / 2);
	update_cam_points(data);
	update_proj_orth_matrix(data);
	update_proj_perspect_matrix(data);
	update_screen_points(data);
	ft_bzero(data->img_addr, data->bits_per_pixel * WIN_W * WIN_H / 8);
	put_grid(data, 50);
	put_all_points(data);

//	p5 = vec4f_new(100, 100, 0, 0);
//	p1 = vec4f_new(0, 0, 0, 0);
//	trace_line(data, p5 , p1, RED);
//	p2 = vec4f_new(0, 100, 0, 0);
//	trace_line(data, p5 , p2, RED);
//	p3 = vec4f_new(0, 200, 0, 0);
//	trace_line(data, p5 , p3, RED);
//	p4 = vec4f_new(100, 0, 0, 0);
//	trace_line(data, p5 , p4, RED);
//	p6 = vec4f_new(100, 200, 0, 0);
//	trace_line(data, p5 , p6, RED);
//	p7 = vec4f_new(200, 0, 0, 0);
//	trace_line(data, p5 , p7, RED);
//	p8 = vec4f_new(200, 100, 0, 0);
//	trace_line(data, p5 , p8, RED);
//	p9 = vec4f_new(200, 200, 0, 0);
//	trace_line(data, p5 , p9, RED);
//	p10 = vec4f_new(200, 50, 0, 0);
//	trace_line(data, p5 , p10, BLUE);
//	p11 = vec4f_new(150, 0, 0, 0);
//	trace_line(data, p5 , p11, GREEN);
//	p12 = vec4f_new(150, 200, 0, 0);
//	trace_line(data, p5 , p12, WHITE);
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


