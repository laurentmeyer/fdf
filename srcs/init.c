/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 12:32:54 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/03 17:49:43 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#define INIT_XY 45
#define INIT_XZ -45
#define INIT_ZOOM 30
#define DEF_MIN_COL 0xFFF960
#define DEF_MAX_COL 0xFF60FF

static t_cam	*init_cam(void)
{
	t_cam	*cam;

	if ((cam = (t_cam *)malloc(sizeof(t_cam))))
	{
		cam->xy_angle = INIT_XY * M_PI / 180;
		cam->xz_angle = INIT_XZ * M_PI / 180;
		cam->zoom = INIT_ZOOM;
		cam->znear = 1.0;
		cam->details = 1;
		cam->marks = 0;
		cam->y_scale = 1.0;
		cam->zfar = 1000.0;
		if (!(cam->wtoc = matrix44f_identity())
				|| !(cam->ortho_proj = matrix44f_identity()))
			return (NULL);
	}
	return (cam);
}

static t_vec4f	***init_world_pts_array(t_data *data)
{
	int		i;
	int		j;
	t_vec4f	***dest;

	if (!(dest = (t_vec4f ***)malloc((data->lines + 2) * sizeof(t_vec4f **)))
		|| !(dest[data->lines] = (t_vec4f **)malloc(5 * sizeof(t_vec4f *)))
		|| !(dest[data->lines + 1] = (t_vec4f **)malloc(sizeof(t_vec4f *))))
		return (NULL);
	i = 0;
	while (i < data->lines)
	{
		if (!(dest[i] = (t_vec4f **)malloc((data->cols + 1)
						* sizeof(t_vec4f *))))
			return (NULL);
		j = 0;
		while (j < data->cols + 1)
			dest[i][j++] = NULL;
		++i;
	}
	i = 0;
	while (i < 5)
		dest[data->lines][i++] = NULL;
	dest[data->lines + 1][0] = NULL;
	return (dest);
}

static t_vec4f	***init_other_pts_array(t_data *data)
{
	int		i;
	int		j;
	t_vec4f	***dest;

	if (!(dest = (t_vec4f ***)malloc((data->lines + 2) * sizeof(t_vec4f **)))
			|| !(dest[data->lines + 1] = (t_vec4f **)malloc(sizeof(t_vec4f *))))
		return (NULL);
	i = 0;
	while (i < data->lines + 1)
	{
		j = 0;
		while ((data->world_pts)[i][j])
			++j;
		if (!(dest[i] = (t_vec4f **)malloc((j + 1) * sizeof(t_vec4f *))))
			return (NULL);
		dest[i][j--] = NULL;
		while (j-- >= 0)
			dest[i][j + 1] = vec4f_dup((data->world_pts)[i][j + 1]);
		++i;
	}
	dest[data->lines + 1][0] = NULL;
	return (dest);
}

static int		find_min_max_height(t_data *data)
{
	float		min;
	float		max;
	float		tmp;
	int			i;
	int			j;

	min = (*((data->world_pts)[0][0]))[1];
	max = min;
	i = 0;
	while (i++ < data->lines)
	{
		j = 0;
		while ((data->world_pts)[i - 1][j])
		{
			if ((tmp = (*((data->world_pts)[i - 1][j]))[1]) < min)
				min = tmp;
			if ((tmp = (*((data->world_pts)[i - 1][j]))[1]) > max)
				max = tmp;
			++j;
		}
	}
	data->min_y = min;
	data->max_y = max;
	return (1);
}

t_data			*init_data(char *path)
{
	t_data	*data;

	if ((data = (t_data *)malloc(sizeof(t_data))))
	{
		if (!(data->ptr = mlx_init())
				|| !(data->win = mlx_new_window(data->ptr, WIN_W, WIN_H, WIN_T))
				|| !(data->img_ptr = mlx_new_image(data->ptr, WIN_W, WIN_H))
				|| !(data->img_addr = mlx_get_data_addr(data->img_ptr,
						&(data->bits_per_pixel),
						&(data->size_line), &(data->endian)))
				|| !(data->min_col = DEF_MIN_COL)
				|| !(data->max_col = DEF_MAX_COL)
				|| !file_dimensions(path, data)
				|| !(data->world_pts = init_world_pts_array(data))
				|| !fill_world_pts(path, data)
				|| !find_min_max_height(data)
				|| !(center_pts_array(data))
				|| !(data->cam_pts = init_other_pts_array(data))
				|| !(data->screen_pts = init_other_pts_array(data))
				|| !(data->cam = init_cam()))
			return (NULL);
	}
	return (data);
}
