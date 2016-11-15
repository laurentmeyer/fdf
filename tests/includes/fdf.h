/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 16:49:15 by lmeyer            #+#    #+#             */
/*   Updated: 2016/11/15 19:25:22 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# define WIN_W 640
# define WIN_H 480
# define WIN_T "Test window"
# define PIX_BITS 24
# define ENDIAN 0
// liste des touches : /System/Library/Frameworks/Carbon.framework/Versions/A/Frameworks/HIToolbox.framework/Versions/A/Headers/Events.h
# define ESC_KEY 0x35
# define LeftArrow 0x7B
# define RightArrow 0x7C
# define DownArrow 0x7D
# define UpArrow 0x7E
# define WHITE 0xFFFFFF
# define BLACK 0x000000

typedef struct		s_img
{
	void			*img;
	char			*addr;
	int				l_size;
}					t_img;

typedef struct		s_data
{
	void			*ptr;
	void			*win;
	t_img			*img;
	t_list			*plist;
	t_list			*qlist;
	int				pts_pl;
}					t_data;

typedef struct		s_pt
{
	int				x;
	int				y;
	int				z;
	int				w;
	int				px;
	int				py;
	int				pz;
}					t_pt;

t_data				*init_data(void);
t_img				*init_image(t_data *data);
t_pt				*init_point(int x, int y, int z);
int					fill_plist(int fd, t_data *data);
int					display_image(t_data *data);
int					key_hooks(int keycode,void *data);

#endif
