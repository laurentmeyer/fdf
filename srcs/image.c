/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 17:53:56 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/15 19:11:49 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

t_img	*init_image(t_data *data)
{
	t_img	*image;
	int		endian;
	int		pix_bits;

	endian = ENDIAN;
	pix_bits = PIX_BITS;
	if (!(image = (t_img *)malloc(sizeof(t_img))))
	{
		if (!(image->img = mlx_new_image(data->ptr, WIN_W, WIN_H)))
			return (NULL);
		image->l_size = sizeof(int) * WIN_W;
		if (!(image->addr = mlx_get_data_addr(image->img, &pix_bits,
						&(image->l_size), &endian)))
			return (NULL);
	}
	return (image);
}
