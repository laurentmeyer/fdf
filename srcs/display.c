/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 21:41:41 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/25 21:53:13 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void	pixel_put(t_data *data, int x, int y, int color)
{
	((unsigned int *)(data->img_addr))[y * WIN_W + x]
		= mlx_get_color_value(data->ptr, color);
}

void	print_data_details(t_data *data)
{
	mlx_string_put(data->ptr, data->win, 150, 150, WHITE, "coucou\nc'est moi");
}

int		display_image(t_data *data)
{
	put_grid(data, 50);
	put_all_points(data);
	if (!mlx_put_image_to_window(data->ptr, data->win, data->img_ptr, 0, 0))
		exit(0);
	print_data_details(data);
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
		while (j < data->cols)
		{
			pt = (data->world_pts)[i][j];
			pixel_put(data, (*pt)[0], (*pt)[2], WHITE);
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
