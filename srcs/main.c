/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:10:17 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/02 13:44:07 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

#include <stdio.h>

int		main(int ac, char **av)
{
	t_data		*data;

	if (ac == 2 && (data = init_data(av[1])))
		display_image(data);
	return (0);
}
