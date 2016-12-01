/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 14:06:36 by lmeyer            #+#    #+#             */
/*   Updated: 2016/12/01 12:03:14 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include "vectors.h"
# include "matrices.h"
# define WIN_W 1024
# define WIN_H 768
# define INIT_XY 0
# define INIT_XZ 0
# define WIN_T "Test window"
# define WHITE 0x00FFFFFF
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define BLACK 0x000000
# define DARK_GRAY 0x222222


typedef struct		s_cam
{
	float			xy_angle;
	float			xz_angle;
	float			distance;
	t_matrix44f		*wtoc;
	float			znear;
	float			zfar;
	float			theta;
	t_matrix44f		*ortho_proj;
	t_matrix44f		*perspect_proj;
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
	t_cam			*cam;
	t_vec4f			***world_pts;
	t_vec4f			***cam_pts;
	t_vec4f			***screen_pts;
	float			*zbuffer;
}					t_data;

int					file_dimensions(char *path, t_data *data);
int					fill_world_pts(char *path, t_data *data);
t_data				*init_data(char *path);
t_vec4f				*init_vec4f(float x, float y, float z, float w);
int					display_image(t_data *data);
int					key_hooks(int keycode, void *data);
void				update_camera(t_data *data);
void				pixel_put(t_data *data, int x, int y, int color);
void				print_data_details(t_data *data);
int					display_image(t_data *data);
void				put_all_points(t_data *data);
void				put_grid(t_data *data, int step);
void				update_proj_perspect_matrix(t_data *data);
void				update_proj_orth_matrix(t_data *data);
void				trace_line(t_data *data, t_vec4f *a, t_vec4f *b, int color);
void				trace_all_lines(t_data *data);

void	print_point(t_vec4f *pt);
void	print_points_array(t_data *data, t_vec4f ***a);
void	print_all_points(t_data *data);
void	update_cam_points(t_data *data);
void	update_camera(t_data *data);


#endif
