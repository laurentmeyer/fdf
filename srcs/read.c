/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 13:48:59 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/02 11:41:43 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX_STR 20

#include <stdio.h>

static char	*get_next_element(char *s, char buffer[MAX_STR])
{
	int		i;

	while (*s == ' ')
		++s;
	i = 0;
	while (*s != 0 && *s != ' ' && i < MAX_STR - 1)
		buffer[i++] = *(s++);
	buffer[i] = '\0';
	while (*s == ' ')
		++s;
	return (s);
}

int		file_dimensions(char *path, t_data *data)
{
	char	*line;
	int		fd;
	int		gnl;
	int		c;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	data->lines = 0;
	data->cols = 0;
	while ((gnl = get_next_line(fd, &line)))
	{
		if (gnl == -1)
			return (0);
		++(data->lines);
		if ((c = ft_countwords(line, ' ')) > data->cols)
			data->cols = c;
		free(line);
	}
	return ((close(fd) == -1) ? 0 : 1);
}

static int		fill_one_line(t_data *data, char *line, int i)
{
	int		j;
	char	buffer[MAX_STR];

	j = 0;
	while (*line)
	{
		line = get_next_element(line, buffer);
		if (!((data->world_pts)[i][j] = vec4f_new((float)j,
				(float)ft_atoi(buffer), (float)i, 1.0)))
			return (0);
		++j;
	}
	return (1);
}

int		fill_world_pts(char *path, t_data *data)
{
	char	*line;
	int		fd;
	int		i;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	i = 0;
	while (i < data->lines)
	{
		if (get_next_line(fd, &line) == -1
				|| !fill_one_line(data, line, i++))
			return (0);
		free(line);
	}
	if (!((data->world_pts)[data->lines][0] = vec4f_new(0.0, 0.0, 0.0, 1.0))
			|| !((data->world_pts)[data->lines][1]
				= vec4f_new(1.0, 0.0, 0.0, 1.0))
			|| !((data->world_pts)[data->lines][2]
				= vec4f_new(0.0, 1.0, 0.0, 1.0))
			|| !((data->world_pts)[data->lines][3]
				= vec4f_new(0.0, 0.0, 1.0, 1.0)))
		return (0);
	return ((close(fd) == -1) ? 0 : 1);
}
