/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:10:17 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/05 16:49:29 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int		main(int ac, char **av)
{
	t_data		*data;
	int			i;

	if (ac == 1)
		ft_putstr("usage: fdf file [-min] [-max]\n");
	else if ((i = open(av[1], O_RDONLY)) == -1 || close(i) == -1)
		ft_putstr("wrong file\n");
	else if ((data = init_data(av[1])))
	{
		i = 0;
		while (++i < ac)
		{
			if (ft_strequ(av[i - 1], "-min") && ft_is_hex_str(av[i]))
				data->min_col = ft_atoi_hex(av[i]);
			if (ft_strequ(av[i - 1], "-max") && ft_is_hex_str(av[i]))
				data->max_col = ft_atoi_hex(av[i]);
		}
		update_camera(data);
		display_image(data);
	}
	return (0);
}
