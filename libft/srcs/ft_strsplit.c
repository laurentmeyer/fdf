/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:35:52 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/21 16:36:24 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

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

char		**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;
	int		w;

	w = countwords(s, c);
	if ((arr = (char **)malloc((w + 1) * sizeof(char *))))
	{
		i = 0;
		while (i < w)
		{
			while (*s == c)
				++s;
			j = 0;
			while (*(s + j) != c)
				++j;
			if ((arr[i] = ft_strnew(j)))
				ft_strncpy(arr[i++], s, j);
			s += j;
		}
		arr[i] = 0;
	}
	return (arr);
}
