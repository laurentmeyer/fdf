/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_basics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:59:52 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/25 18:34:43 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

void				print_matrix(t_matrix44f *a)
{
	int		i;

	i = -1;
	printf("\n=================================================\n");
	while (++i < 4)
		printf("%f %f %f %f\n", (*a)[i][0], (*a)[i][1], (*a)[i][2], (*a)[i][3]);
}

t_matrix44f			*matrix44f_identity(void)
{
	float	tmp[4][4];

	ft_bzero(tmp, sizeof(tmp));
	tmp[0][0] = 1;
	tmp[1][1] = 1;
	tmp[2][2] = 1;
	tmp[3][3] = 1;
	return (matrix44f_dup((t_matrix44f *)(&tmp)));
}

t_matrix44f			*matrix44f_dup(t_matrix44f *a)
{
	t_matrix44f	*tmp;

	if ((tmp = (t_matrix44f *)malloc(sizeof(t_matrix44f))))
		ft_memcpy(tmp, a, sizeof(t_matrix44f));
	return (tmp);
}

void			axb_matrix44f(t_matrix44f *to_change, t_matrix44f *mult)
{
	float	tmp[4][4];
	int		i;
	int		j;

	ft_memcpy(&tmp, to_change, sizeof(t_matrix44f));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			(*to_change)[i][j] = tmp[i][0] * (*mult)[0][j]
								+ tmp[i][1] * (*mult)[1][j]
								+ tmp[i][2] * (*mult)[2][j]
								+ tmp[i][3] * (*mult)[3][j];
			++j;
		}
		++i;
	}
}
