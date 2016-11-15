/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 18:41:22 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/15 19:28:06 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>


//int		is_in_circle(t_pt *origin, t_pt *point, int rayon)
//{
//	if (distance(origin, point) <= rayon)
//		return (1);
//	return (0);
//}
//
//void		draw_point(t_img *img, t_pt *pt, int color)
//{
//	ft_memcpy(img->addr + (pt->x + pt->y * img->win_w) * sizeof(int),
//				&color,
//				sizeof(int));
//}
//
//void		draw_circle(t_img *img, t_pt *center, int rayon, int color)
//{
//	int		x;
//	int		y;
//	int		i;
//
//	i = 0;
//	while (i < img->win_w * img->win_h)
//	{
//		x = i % img->win_w;
//		y = i / img->win_w;
//		if (lround(sqrt((x - center->x) * (x - center->x)
//					+ (y - center->y) * (y - center->y))) <= rayon)
//			ft_memcpy(img->addr + i * sizeof(int), &color, sizeof(int));
//		++i;
//	}
//}
//
//
//int		draw_in_image(t_img *image, t_list *points)
//{
//	//draw_circle(image, image->center, 10, WHITE);
//	while (points->next)
//	{
//		draw_point(image, (t_pt *)(points->content), WHITE);
//		points = points->next;
//	}
//	return (1);
//}
//
//void	test(int fd)
//{
//	void	*ptr;
//	t_img	*img;
//	t_list	*points;
//
//	if (!(ptr = mlx_init())
//			|| !(img = init_image(ptr, WIN_W, WIN_H, WIN_TITLE))
//			|| !read_input(fd, &points)
//			|| !draw_in_image(img, points)
//			|| !mlx_put_image_to_window(img->ptr, img->win, img->img, 0, 0))
//		exit(0);
//	mlx_key_hook(img->win, &key_hooks, img);
//	mlx_loop(img->ptr);
//}

int		display_image(t_data *data)
{
	if (!mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0))
		exit(0);
	mlx_key_hook(data->win, &key_hooks, data);
	mlx_loop(data->ptr);
	return (1);
}
