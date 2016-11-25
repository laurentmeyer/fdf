/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 19:58:28 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/25 20:31:34 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRICES_H
# define MATRICES_H

typedef	float		t_matrix44f[4][4];

t_matrix44f			*matrix44f_identity(void);
t_matrix44f			*matrix44f_dup(t_matrix44f *a);
void				axb_matrix44f(t_matrix44f *to_change, t_matrix44f *mult);
void				print_matrix(t_matrix44f *a);
void				matrix44f_translation(t_matrix44f *a, float x, float y, float z);
void				matrix44f_scale(t_matrix44f *a, float x, float y, float z);
void				matrix44f_rotation_x(t_matrix44f *a, float radians);
void				matrix44f_rotation_y(t_matrix44f *a, float radians);
void				matrix44f_rotation_z(t_matrix44f *a, float radians);

#endif
