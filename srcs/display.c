/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 18:41:22 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/16 21:55:25 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

#include <stdio.h>

//int		is_in_circle(t_pt *origin, t_pt *point, int rayon)
//{
//	if (distance(origin, point) <= rayon)
//		return (1);
//	return (0);
//}
//
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

void	print_plist(t_data *data)
{
	t_list	*plist;
	t_pt	*pt;

	plist = data->plist;
	while (plist)
	{
		pt = (t_pt *)(plist->content);
		printf("x = %d y = %d\n", pt->x, pt->y);
		plist = plist->next;
	}
}

void		print_address(t_data *data)
{
	int	i;

	i = 0;
	while (i < WIN_H * WIN_W)
	{
		printf("%d\n", *((int *)(data->img->addr + i * sizeof(int))));
		i += 1;
	}
}

void		print_point(t_data *data, t_pt *pt, int color)
{
	if (pt->x < WIN_W && pt->x >= 0 && pt->y < WIN_H && pt->y >= 0)
		ft_memcpy(data->img->addr + (pt->x + pt->y * WIN_W) * sizeof(int),
				&color,
				sizeof(int));
}

int		point_color(t_pt *pt)
{
	if (pt)
		;
	return (0xFF00FF);
}

void	print_points(t_data *data)
{
	t_list	*plist;
	t_pt	*pt;

	//print_plist(data);
	plist = data->plist;
	while (plist)
	{
		pt = (t_pt *)(plist->content);
//		printf("x = %d y = %d\n", pt->x, pt->y);
		print_point(data, pt, point_color(pt));
		plist = plist->next;
	}
}

int		display_image(t_data *data)
{
	print_points(data);
	print_address(data);
	if (!mlx_put_image_to_window(data->ptr, data->win, data->img->img_ptr, 0, 0))
		exit(0);
	mlx_key_hook(data->win, &key_hooks, data);
	mlx_loop(data->ptr);
	return (1);
}
