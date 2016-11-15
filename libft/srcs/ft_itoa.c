/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:40:09 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/04 16:12:27 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_intlen(int n)
{
	if (n == MININT)
		return (MININTSIZE);
	else if (n < 0)
		return (1 + ft_intlen(-n));
	else if (n < 10)
		return (1);
	else
		return (1 + ft_intlen(n / 10));
}

char		*ft_itoa(int n)
{
	char	*tmp;
	int		l;

	l = ft_intlen(n);
	if (n == MININT)
		tmp = ft_strdup(MININTSTR);
	else if ((tmp = ft_strnew(l)))
	{
		if (n < 0)
		{
			tmp[0] = '-';
			n = -n;
		}
		while (n >= 10)
		{
			tmp[--l] = n % 10 + '0';
			n /= 10;
		}
		tmp[--l] = n % 10 + '0';
	}
	return (tmp);
}
