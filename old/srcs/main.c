/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 16:49:07 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/16 17:18:29 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

int		main(int ac, char **av)
{
	int		fd;
	t_data	*data;

	if (ac != 2)
		ft_putstr("Erreur\n");
	if ((fd = open(av[1], O_RDONLY)) != -1
			&& (data = init_data())
			&& fill_plist(fd, data)
//			&& fill_qlist(fd, data))
			&& display_image(data))
		close(fd);
	return (0);
}
