/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 17:33:45 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/28 18:07:04 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include "matrices.h"

typedef float		t_vec4f[4];

t_vec4f				*vec4f_new(float x, float y, float z, float w);
t_vec4f				*vec4f_dup(t_vec4f *v);
void				m44f_x_vec4f(t_matrix44f *m, t_vec4f *v);
void				m44f_x_vec4f_to(t_vec4f *dest, t_matrix44f *m, t_vec4f *v);

#endif
