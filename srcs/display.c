/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 21:41:41 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/02 19:18:39 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <math.h>
#define PIX_PER_LINE 20
#define PIX_PER_CHAR 10
#include <stdio.h>

void	pixel_put(t_data *data, int x, int y, int color)
{
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	((unsigned int *)(data->img_addr))[y * WIN_W + x]
		= mlx_get_color_value(data->ptr, color);
}

void	print_label(t_data *data, int line, char *label, float value)
{
	mlx_string_put(data->ptr, data->win, 0, line * PIX_PER_LINE, WHITE, label);
	mlx_string_put(data->ptr, data->win, PIX_PER_CHAR * ft_strlen(label),
			line * PIX_PER_LINE, WHITE, ft_itoa((int)value));
}

void	print_data_details(t_data *data)
{
	int		i;

	i = 0;
	if (!data->cam->details)
		return ;
	print_label(data, i++, "Y factor x100: ", 100 * data->cam->y_scale);
	print_label(data, i++, "         Zoom: ", data->cam->zoom);
	print_label(data, i++, "     XY angle: ", data->cam->xy_angle * 180 / M_PI);
	print_label(data, i++, "     XZ angle: ", data->cam->xz_angle * 180 / M_PI);
	print_label(data, i++, "     Marks on: ", data->cam->marks);
	print_label(data, i++, "        min Y: ", 100 *data->min_y);
	print_label(data, i++, "        max Y: ", 100 * data->max_y);
//	mlx_string_put(data->ptr, data->win, 0, 0, WHITE, "................");
//	mlx_string_put(data->ptr, data->win, 0, 5, WHITE, "________________");
}

int		display_image(t_data *data)
{
 	mlx_key_hook(data->win, &key_hooks, data);
	mlx_loop(data->ptr);
	return (1);
}

void	put_all_points(t_data *data)
{
	int			i;
	int			j;
	t_vec4f		*pt;

	i = 0;
	while (i < data->lines)
	{
		j = 0;
		while ((data->screen_pts)[i][j])
		{
			pt = (data->screen_pts)[i][j];
//			print_point(pt);
//			printf("color : %x\n", (int)((*pt)[2]));
			pixel_put(data, (int)((*pt)[0]),
					(int)((*pt)[1]), (int)((*pt)[2]));
//					color_for_height(data->min_y,
//						data->max_y,
//						(*(((data->world_pts)[i][j])))[1]));
			++j;
		}
		++i;
	}
	return ;
}

void	put_grid(t_data *data, int step)
{
	int		x;
	int		y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (x % step == 0 || y % step == 0)
				pixel_put(data, x, y, DARK_GRAY);
			++x;
		}
		++y;
	}
}
