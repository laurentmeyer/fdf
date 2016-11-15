/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 18:22:16 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/15 19:13:21 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

int		key_hooks(int keycode,void *data)
{
	t_img	*img;

	img = ((t_data *)data)->img;
	if (keycode == ESC_KEY)
		exit(0);
//	if (keycode == LeftArrow)
//		img->center->x -= 10;
//	if (keycode == RightArrow)
//		img->center->x += 10;
//	if (keycode == DownArrow)
//		img->center->y += 10;
//	if (keycode == UpArrow)
//		img->center->y -= 10;
//	if (!clear_image(img)
//			|| !draw_in_image(img, )
//			|| !mlx_put_image_to_window(img->ptr, img->win, img->img, 0, 0))
//		return (0);
	return (1);
}
