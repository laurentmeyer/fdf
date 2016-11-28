/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 16:58:25 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/28 12:50:32 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	print_point(t_vec4f *pt)
{
	printf("x = %f y = %f z = %f\n", (*pt)[0], (*pt)[1], (*pt)[2]);
}

void	print_points_array(t_data *data, t_vec4f ***a)
{
	int		i;
	int		j;

	i = 0;
	while (i < data->lines)
	{
		j = -1;
		while (++j < data->cols)
			print_point(a[i][j]);
		++i;
	}
}

void				print_matrix(t_matrix44f *a)
{
	int		i;

	i = -1;
	printf("\n=================================================\n");
	while (++i < 4)
		printf("%f %f %f %f\n", (*a)[i][0], (*a)[i][1], (*a)[i][2], (*a)[i][3]);
}

