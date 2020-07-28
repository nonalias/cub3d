/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dochoi_cub3D.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dochoi <dochoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 00:04:40 by dochoi            #+#    #+#             */
/*   Updated: 2020/07/22 14:07:31 by dochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOCHOI_CUB3D_H
# define DOCHOI_CUB3D_H

# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

# define WIN_WIDTH				1024
# define WIN_HEIGHT				512

# define KEY_PRESS_EVENT		2
# define KEY_RELEASE_EVENT		3
# define MOUSE_X_EVENT			17
# define KEY_A					0
# define KEY_D					2
# define KEY_W					13
# define KEY_S					1
# define KEY_LEFT				123
# define KEY_RIGHT				124
# define KEY_JUMP				49

# define DR						0.0174533

# define DEFAULT_CEILING_COLOR	0x50BCDF
# define DEFAULT_FLOOR_COLOR	0x473C36

# define MAX_WIN_WIDTH			1600
# define MIN_WIN_WIDTH			450
# define MAX_WIN_HEIGHT			900
# define MIN_WIN_HEIGHT			450

typedef struct					s_sp_list
{
	float						dochoi_sp_x;
	float						dochoi_sp_y;
	float						dist_sp;
	int							mx;
	int							my;
	int							type;
	struct s_sp_list			*next;
}								t_sp_list;

typedef struct					s_img
{
	void						*img_ptr;
	int							*data;
	int							size_l;
	int							bpp;
	int							endian;
	int							width;
	int							height;
}								t_img;

typedef struct					s_player
{
	float						x;
	float						y;
	float						dx;
	float						dy;
	float						angle;
	int							jump_cnt;
	int							down_cnt;
	int							life;
}								t_player;

typedef struct					s_ray
{
	int							r;
	int							mx;
	int							my;
	int							mp;
	int							dof;
	int							sp_flag;
	int							map_dochoi_x;
	int							map_dochoi_x2;
	int							map_dochoi_y;
	int							h_so_flag;
	int							v_ea_flag;
	int							v_close_flag;
	int							count_w;
	int							count_h;
	int							idx;
	int							temp;
	int							line_width;
	int							max_line_width;
	int							sp_type;
	float						rx;
	float						ry;
	float						ra;
	float						xo;
	float						yo;
	float						dist;
	float						dist2;
	float						dist_h;
	float						dist_v;
	float						dist_sp;
	float						dist_sp_h;
	float						dist_sp_v;
	float						atan_ra;
	float						n_tan;
	float						dochoi_sp_x;
	float						dochoi_sp_y;
	float						prey;
	float						prex;
	float						hy;
	float						hx;
	float						vy;
	float						vx;
	float						ca;
	float						line_h;
	float						line_h_sp;
	float						line_o;
	float						line_o_sp;
	float						temp2;
	float						inter;
	float						dr_dochoi;
	float						angle_user_to_sp;
	float						max_rad_sp;
	float						min_rad_sp;
	float						cur;
	float						min_max_cur_ra;
	t_sp_list					*sp_list;
	int							die;
}								t_ray;

typedef struct					s_mlx
{
	void						*mlx_ptr;
	void						*win;
	t_player					player;
	int							key_check[300];
	int							win_w;
	int							win_h;
	t_img						no_wall;
	t_img						so_wall;
	t_img						we_wall;
	t_img						ea_wall;
	t_img						sp;
	t_img						img;
	t_img						ani[3];
	t_img						*ani_bone;
	t_img						hud;
	t_img						door;
	int							color;
	int							f_color;
	int							c_color;
	int							**map;
	int							flag_check[8];
	int							map_w;
	int							map_h;
	char						dir;
	int							save_flag;
	int							max_dof;
	int							dir_flag;
	int							cnt;
	t_ray						ray;
}								t_mlx;

void							split_free(char **strs);
int								what_flag_r(char **strs, t_mlx *mlx);
int								what_flag_no(char **strs, t_mlx *mlx);
int								what_flag_so(char **strs, t_mlx *mlx);
int								what_flag_we(char **strs, t_mlx *mlx);
int								what_flag_ea(char **strs, t_mlx *mlx);
int								what_flag_s(char **strs, t_mlx *mlx);
int								what_flag_f(char **strs, t_mlx *mlx);
int								what_flag_c(char **strs, t_mlx *mlx);
int								display_error(char *msg);
int								map_parse(t_mlx *mlx, char *filename);
int								array_parse_2(t_mlx *mlx, char *str, int *flag);
void							map_init(t_mlx *mlx);
void							player_set(t_mlx *mlx);
int								key_press_event_func(int keycode, t_mlx *mlx);
int								key_release_event_func(int keycode, t_mlx *mlx);
float							dist(float ax, float ay, float bx, float by);
int								dochoi_show(t_mlx *mlx);
void							h_check(t_mlx *mlx);
float							dist(float ax, float ay, float bx, float by);
void							show_wall(t_mlx *mlx);
void							key_loop(t_mlx *mlx);
void							v_check(t_mlx *mlx);
void							show_sprite(t_mlx *mlx);
void							show_c_f(t_mlx *mlx);
void							map_check(t_mlx *mlx);
t_sp_list						*ft_lstnew_sp(t_mlx *mlx, int is_v,
int mx, int my);
void							ft_lstclear_sp(t_sp_list **lst);
void							ft_lstadd_back_sp(t_sp_list **lst,
t_sp_list *new);
void							ft_list_sort_sp(t_sp_list **begin_list);
void							show_hud(t_mlx *mlx);
void							show_life(t_mlx *mlx);
int								save_bmp(t_mlx *mlx);
void							v_check3(t_mlx *mlx);
void							set_dark(t_mlx *mlx, float r_dist);

#endif
