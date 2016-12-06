/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 16:58:25 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/03 16:49:29 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#define PIX_PER_LINE 20
#define PIX_PER_CHAR 10

void	print_label(t_data *data, int line, char *label, float value)
{
	char *tmp;

	if ((tmp = ft_itoa((int)value)))
	{
		mlx_string_put(data->ptr, data->win, 0,
						line * PIX_PER_LINE, WHITE, label);
		mlx_string_put(data->ptr, data->win, PIX_PER_CHAR * ft_strlen(label),
				line * PIX_PER_LINE, WHITE, tmp);
		free(tmp);
	}
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
	print_label(data, i++, "        min Y: ", 100 * data->min_y);
	print_label(data, i++, "        max Y: ", 100 * data->max_y);
}
