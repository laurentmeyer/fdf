/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:10:17 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/25 21:53:11 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

#include <stdio.h>

int		main(void)
{
	t_data		*data;
//	t_vec4f		*a;
//	t_vec4f		*b;
//	t_vec4f		*c;
//	t_vec4f		*d;
//
//	a = vec4f_new(100, 0, 100, 1);
//	b = vec4f_new(200, 0, 100, 1);
//	c = vec4f_new(100, 0, 200, 1);
//	d = vec4f_new(200, 0, 200, 1);

	if ((data = init_data()))
	{
//		(data->world_pts)[0][0] = a;
//		(data->world_pts)[0][1] = b;
//		(data->world_pts)[1][0] = c;
//		(data->world_pts)[1][1] = d;
		display_image(data);
	}
	return (0);
}
