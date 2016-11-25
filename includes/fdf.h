/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 14:06:36 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/25 21:53:09 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
#include "vectors.h"
#include "matrices.h"
# define WIN_W 500
# define WIN_H 500
# define WIN_T "Test window"
# define WHITE 0x00FFFFFF
# define BLACK 0x000000
# define DARK_GRAY 0x222222

typedef struct		s_cam
{
	float			xy_angle;
	float			xz_angle;
	int				distance;
	t_matrix44f		*wtoc;
//	t_matrix44f		*ctow;
	float			znear;
	float			theta;
}					t_cam;

typedef struct		s_data
{
	void			*ptr;
	void			*win;
	void			*img_ptr;
	char			*img_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				cols;
	int				lines;
	t_vec4f			***world_pts;
	t_vec4f			***cam_pts;
	t_cam			*cam;
	float			*zbuffer;
}					t_data;


t_data				*init_data(void);
t_vec4f				*init_vec4f(float x, float y, float z, float w);
int					display_image(t_data *data);
int					key_hooks(int keycode, void *data);
void				update_camera(t_data *data);
void				pixel_put(t_data *data, int x, int y, int color);
void				print_data_details(t_data *data);
int					display_image(t_data *data);
void				put_all_points(t_data *data);
void				put_grid(t_data *data, int step);

#endif
