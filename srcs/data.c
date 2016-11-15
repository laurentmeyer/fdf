/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 17:19:03 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/15 19:14:57 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>

t_data				*init_data(void)
{
	t_data	*data;

	if ((data = (t_data *)malloc(sizeof(t_data))))
	{
		if (!(data->ptr = mlx_init())
				|| !(data->win = mlx_new_window(data, WIN_W, WIN_H, WIN_T))
				|| !(data->img = init_image(data)))
			return (NULL);
		data->plist = NULL;
		data->qlist = NULL;
	}
	return (data);
}
