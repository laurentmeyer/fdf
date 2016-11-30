/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 21:41:41 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/30 18:32:59 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <stdio.h>

void	pixel_put(t_data *data, int x, int y, int color)
{
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	((unsigned int *)(data->img_addr))[y * WIN_W + x]
		= mlx_get_color_value(data->ptr, color);
}

void	print_data_details(t_data *data)
{
	mlx_string_put(data->ptr, data->win, 0, 0, WHITE, "salut c'est cool");
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
			pixel_put(data, (int)((*pt)[0]), (int)((*pt)[1]), WHITE);
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
