/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 18:42:12 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/15 19:05:31 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#define SPREAD 10

int		free_str_array(char **arr)
{
	while (*arr)
		free((*arr)++);
	free(arr);
	return (1);
}

int		str_arr_len(char **arr)
{
	int	i;

	i = 0;
	while ((*arr)++)
		++i;
	return (i);
}

int		fill_list(char **arr, char **line, t_list **alist, int lnum)
{
	t_pt	*pt;
	t_list	*new;
	int		i;

	i = 0;
	while (arr[i])
	{
		if (!(pt = init_point(i * SPREAD, lnum * SPREAD, ft_atoi(arr[i])))
				|| !(new = ft_lstnew(pt, sizeof(pt))))
			return (0);
		ft_lstadd(alist, new);
		free(pt);
		free(new);
		free(line);
		free_str_array(arr);
	}
	return (1);
}

int		fill_plist(int fd, t_data *data)
{
	int		gnl;
	char	**line;
	char	**arr;
	int		l;

	line = NULL;
	if ((gnl = get_next_line(fd, line)) == -1
			|| !(arr = ft_strsplit(*line, ' '))
			|| (data->pts_pl = str_arr_len(arr)) == 0)
		return (0);
	l = 0;
	fill_list(arr, line, &(data->plist), l);
	while ((gnl = get_next_line(fd, line)))
	{
		++l;
		if (gnl == -1
				|| !(arr = ft_strsplit(*line, ' '))
				|| str_arr_len(arr) != data->pts_pl)
			return (0);
		fill_list(arr, line, &(data->plist), l);
	}
	return (1);
}
