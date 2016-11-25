/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 15:06:17 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/21 16:36:19 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static	int	countwords(char const *s, char c)
{
	if (c == '\0')
		return ((*s == '\0') ? 0 : 1);
	while (*s == c)
		s++;
	if (*s == '\0')
		return (0);
	while (*s != c && *s != '\0')
		s++;
	return (1 + countwords(s, c));
}

int			file_dimensions(t_data *data, char *name)
{
	char	*line;
	int		fd;
	int		gnl;

	if ((fd = open(name, O_RDONLY)) == -1)
		return (0);
	if ((gnl = get_next_line(fd, &line)) != 1
			|| (data->cols = countwords(line, ' ')) == 0)
		return (0);
	data->lines = 1;
	while ((gnl = get_next_line(fd, &line)))
	{
		if (gnl == -1
			|| countwords(line, ' ') != data->cols)
			return (0);
	++data->lines;
	}
	close(fd);
	return (1);
}

int		read_map(t_data *data, char *name)
{
	int		acc;
	int		lnum;
	char	*line;
	char	**arr;

	acc = 0;
	if ((data->world_pts = (t_vec4f **)malloc(data->lines * sizeof(t_vec4f *))))
	{
		lnum = 0;
		get_next_line(fd, &line);
		if (!(data->world_pts[lnum] = ft_strsplit(line, ' '))
				|| (data->pts_pl = str_arr_len(arr)) == 0)

	}
	return (acc);
}

t_data				*init_data(char *filename)
{
	t_data	*data;

	if ((data = (t_data *)malloc(sizeof(t_data))))
	{
		if (!(data->ptr = mlx_init())
				|| !(data->win = mlx_new_window(data, WIN_W, WIN_H, WIN_T))
				|| !(data->img_ptr = mlx_new_image(data->ptr, WIN_W, WIN_H))
				|| !(data->img_addr = mlx_get_data_addr(data->img_ptr,
						data->bits_per_pixel, data->size_line, data->endian))
				|| !file_dimensions(filename)
				|| !read_map(data, filename)
				|| !(data->zbuffer = (float *)malloc(data->cols * data->lines
						* sizeof(float))))
			return (NULL);
	}
	return (data);
}

#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#define SPREAD 1

int		free_str_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (1);
}

int		str_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i++])
		;
	return (i);
}


int		fill_list(char **arr, t_list **alist, int lnum)
{
	t_pt	*pt;
	t_list	*new;
	int		i;

	i = 0;
	while (arr[i])
	{
		if (!(pt = init_point(i * SPREAD, lnum * SPREAD, ft_atoi(arr[i])))
				|| !(new = (t_list *)malloc(sizeof(t_list))))
			return (0);
		new->content_size = sizeof(t_pt);
		new->content = pt;
		ft_lstadd(alist, new);
		++i;
	}
	return (1);
}

int		fill_plist(int fd, t_data *data)
{
	int		gnl;
	char	*line;
	char	**arr;
	int		l;

	if ((gnl = get_next_line(fd, &line)) == -1
			|| !(arr = ft_strsplit(line, ' '))
			|| (data->pts_pl = str_arr_len(arr)) == 0)
		return (0);
	l = 0;
	fill_list(arr, &(data->plist), l);
	free_str_array(arr);
	free(line);
	while ((gnl = get_next_line(fd, &line)))
	{
		if (gnl == -1
				|| !(arr = ft_strsplit(line, ' '))
				|| str_arr_len(arr) != data->pts_pl)
			return (0);
		fill_list(arr, &(data->plist), ++l);
		free_str_array(arr);
		free(line);
	}
	return (1);
}
