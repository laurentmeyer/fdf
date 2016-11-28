/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:02:30 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/28 12:50:35 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <math.h>
#define JUMP 10
#define ESC_KEY 0x35
#define LEFT_KEY 0x7B
#define RIGHT_KEY 0x7C
#define DOWN_KEY 0x7D
#define UP_KEY 0x7E

int		key_hooks(int keycode, void *data)
{
	t_data	*d;

	d = (t_data *)data;
	if (keycode == UP_KEY || keycode == DOWN_KEY)
	{
		d->cam->xy_angle += JUMP * M_PI / 180 * (keycode == UP_KEY ? 1 : -1);
		update_camera(d);
	}
	if (keycode == RIGHT_KEY || keycode == LEFT_KEY)
	{
		d->cam->xz_angle += JUMP * M_PI / 180 * (keycode == RIGHT_KEY ? 1 : -1);
		update_camera(d);
	}
	if (keycode == ESC_KEY)
		exit(0);
	return (1);
}
