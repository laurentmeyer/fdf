/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 17:46:31 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/02 20:36:36 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "matrices.h"
#include <stdlib.h>

#include <stdio.h>

void	put_grid(t_data *data, int step);

void	update_screen_points(t_data *data)
{
	int		i;
	int		j;
	t_vec4f	*src;
	t_vec4f	*dst;

	i = 0;
	while ((data->cam_pts)[i][0])
	{
		j = 0;
		while ((src = (data->cam_pts)[i][j]))
		{
			dst = (data->screen_pts)[i][j];
			if (data->cam->proj == 'o')
				m44f_x_vec4f_to(dst, data->cam->ortho_proj, src);
			if (data->cam->proj == 'p')
				m44f_x_vec4f_to(dst, data->cam->perspect_proj, src);
			(*dst)[0] += WIN_W / 2;
			(*dst)[1] = WIN_H / 2 - (*dst)[1];
//			printf("height = %f\n", (*((data->world_pts)[i][j]))[1]);
			(*dst)[2] = color_for_height(data->min_y, data->max_y,
					(*((data->world_pts)[i][j]))[1]);
			++j;
		}
		++i;
	}
}

void	update_cam_points(t_data *data)
{
	int		i;
	int		j;
	t_vec4f	*src;
	t_vec4f	*dst;

	i = 0;
	while ((data->world_pts)[i][0])
	{
		j = 0;
		while ((src = (data->world_pts)[i][j]))
		{
			dst = (data->cam_pts)[i][j];
			m44f_x_vec4f_to(dst, data->cam->wtoc, src);
			++j;
		}
		++i;
	}
}

void				trace_all_gradients(t_data *data)
{
	int		i;
	int		j;
	t_vec4f	*pt;
	t_vec4f	*next;

	i = 0;
	while (i < data->lines)
	{
		j = 0;
		while ((pt = (data->screen_pts)[i][j])
				&& (next = (data->screen_pts)[i][j++ + 1]))
			trace_gradient(data, pt, next);
		++i;
	}
	i = 0;
	while (i < data->lines - 1)
	{
		j = 0;
		while ((pt = (data->screen_pts)[i][j])
				&& (next = (data->screen_pts)[i + 1][j++]))
			trace_gradient(data, pt, next);
		++i;
	}
}

//void				trace_all_lines(t_data *data)
//{
//	int		i;
//	int		j;
//	t_vec4f	*pt;
//	t_vec4f	*next;
//
//	i = 0;
//	while (i < data->lines)
//	{
//		j = 0;
//		while ((pt = (data->screen_pts)[i][j])
//				&& (next = (data->screen_pts)[i][j++ + 1]))
//			trace_line(data, pt, next, WHITE);
//		++i;
//	}
//	i = 0;
//	while (i < data->lines - 1)
//	{
//		j = 0;
//		while ((pt = (data->screen_pts)[i][j])
//				&& (next = (data->screen_pts)[i + 1][j++]))
//			trace_line(data, pt, next, WHITE);
//		++i;
//	}
//}

void	update_world_height(t_data *data, float coef)
{
	int		i;
	int		j;
	t_vec4f	*pt;

	data->cam->y_scale *= coef;
	i = 0;
	while (i < data->lines)
	{
		j = 0;
		while (j < data->cols)
		{
			if ((pt = (data->world_pts)[i][j]))
				(*pt)[1] *= coef;
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
	matrix44f_scale(data->cam->wtoc, data->cam->zoom, data->cam->zoom,
			data->cam->zoom);
	matrix44f_rotation_y(data->cam->wtoc, data->cam->xz_angle);
	matrix44f_rotation_x(data->cam->wtoc, data->cam->xy_angle);
	update_cam_points(data);
	update_proj_orth_matrix(data);
	update_proj_perspect_matrix(data);
	update_screen_points(data);
	ft_bzero(data->img_addr, data->bits_per_pixel * WIN_W * WIN_H / 8);
	put_grid(data, 50);
	put_all_points(data);
//	trace_all_lines(data);
	trace_all_gradients(data);

	if (data->cam->marks)
	{
		trace_line(data, (data->screen_pts)[data->lines][0],
				(data->screen_pts)[data->lines][1], RED);
		trace_line(data, (data->screen_pts)[data->lines][0],
				(data->screen_pts)[data->lines][2], GREEN);
		trace_line(data, (data->screen_pts)[data->lines][0],
				(data->screen_pts)[data->lines][3], BLUE);
	}
	if (!mlx_put_image_to_window(data->ptr, data->win, data->img_ptr, 0, 0))
		exit(0);
	print_data_details(data);
}
