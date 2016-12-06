/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:02:30 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/03 13:19:17 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <math.h>
#define JUMP 15
#define ESC_KEY 0x35
#define LEFT_KEY 0x7B
#define RIGHT_KEY 0x7C
#define DOWN_KEY 0x7D
#define UP_KEY 0x7E
#define OPEN_KEY 0x21
#define CLOSE_KEY 0x1E
#define PLUS_KEY 0x45
#define MINUS_KEY 0x4e
#define P_KEY 0x23
#define O_KEY 0x1f
#define D_KEY 0x2
#define M_KEY 0x2e

static	void	movement_hooks(int keycode, t_data *d)
{
	if (keycode == DOWN_KEY && 180 / M_PI * d->cam->xy_angle <= 90 - JUMP)
	{
		d->cam->xy_angle += JUMP * M_PI / 180;
		update_camera(d);
	}
	if (keycode == UP_KEY && 180 / M_PI * d->cam->xy_angle >= JUMP)
	{
		d->cam->xy_angle -= JUMP * M_PI / 180;
		update_camera(d);
	}
	if (keycode == LEFT_KEY && 180 / M_PI * d->cam->xz_angle <= 90 - JUMP)
	{
		d->cam->xz_angle += JUMP * M_PI / 180;
		update_camera(d);
	}
	if (keycode == RIGHT_KEY && 180 / M_PI * d->cam->xz_angle >= -90 + JUMP)
	{
		d->cam->xz_angle -= JUMP * M_PI / 180;
		update_camera(d);
	}
}

static	void	zoom_hooks(int keycode, t_data *d)
{
	if (keycode == PLUS_KEY || keycode == MINUS_KEY)
	{
		update_world_height(d, (keycode == PLUS_KEY ? 1.2 : 0.75));
		d->min_y *= (keycode == PLUS_KEY ? 1.2 : 0.75);
		d->max_y *= (keycode == PLUS_KEY ? 1.2 : 0.75);
		update_camera(d);
	}
	if (keycode == OPEN_KEY || keycode == CLOSE_KEY)
	{
		d->cam->zoom *= (keycode == CLOSE_KEY ? 1.1 : 0.9);
		update_camera(d);
	}
}

static	void	other_hooks(int keycode, t_data *d)
{
	if (keycode == M_KEY)
	{
		d->cam->marks = !(d->cam->marks);
		update_camera(d);
	}
	if (keycode == D_KEY)
	{
		d->cam->details = !(d->cam->details);
		update_camera(d);
	}
	if (keycode == ESC_KEY)
		exit(0);
}

int				key_hooks(int keycode, void *data)
{
	movement_hooks(keycode, (t_data *)data);
	zoom_hooks(keycode, (t_data *)data);
	other_hooks(keycode, (t_data *)data);
	return (1);
}
