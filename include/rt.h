/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:23:36 by cschuste          #+#    #+#             */
/*   Updated: 2019/04/17 20:36:56 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
#  define M_PI					3.14159265359
# endif
# include "../lib/libft/libft.h"
# include "../lib/libvec/libvec.h"
# include "kiss_sdl.h"
# include "structs.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define GUI_LBLOCK_W			250
# define GUI_RBLOCK_W			350 + kiss_edge * 3
# define GUI_LBLOCK_H			(RT__H + kiss_edge)
# define GUI_RBLOCK_H			(RT__H + kiss_edge)
# define GUI_EFF_W				175
# define GUI_SBT_SIZE			15
# define GUI_SELECTED_TYPE_OBJ	42
# define GUI_SELECTED_TYPE_LIGHT	43
# define GUI_SELECTED_TYPE_CAM	44

t_light				*get_light_pointer_to_light(t_env *e, int index);
t_lst				*get_lst_pointer_to_light(t_env *e, int index);
double				*get_pointer_to_obj_value(t_env *e, int axis_code);
char				*get_string_obj_type(t_env *e);
void				get_obj_by_click(t_env *e, t_obj **obj, double *c_dist,
									t_lst *temp);
void				gui_handle_events(t_env *e, SDL_Event *ev, int *draw);
void				gui_init_windows(t_env *e);
void				gui_init_entries_0(t_env *e);
void				gui_init_entries_1(t_env *e);
void				gui_init_arrays(t_env *e);
void				gui_init_labels(t_gui *g);
void				update_info(t_env *e);
void				gui_draw(t_env *e);
void				init_gui(t_env *e);
void				draw_all(t_env *e);
int					num_of_lights(t_env *e);

# define MSG_USAGE	"usage: \e[33m./RT scene_file\e[0m"
# define RAY_LENMAX				2147483647
# define RAY_LENMIN				0.001
# define ROT_STEP				15
# define RT__W					800
# define RT__H					800
# define WIN_H					(RT__H + kiss_edge * 4)
# define WIN_W					(RT__W + GUI_LBLOCK_W + GUI_RBLOCK_W)

# define CLR_BACKGROUND			0

# define T_OBJECT				-1
# define T_PLANE				1
# define T_SPHERE				2
# define T_CYLINDER				3
# define T_CONE					4
# define T_PARAB				5
# define T_DISC					6

# define T_AMBIENT				1
# define T_POINT				2
# define T_DIRECTIONAL			3

# define RECURSION				10
# define THREADS				8

void				create_any_ob(t_env *e, unsigned char *arr, t_v pos,
						int spec);
void				sdl_key_press_events(SDL_Event *event, t_env *env);
void				sdl_draw(t_env *env, t_clr color, int x, int y);
void				events_handler(SDL_Event *event, t_env *env);

void				init_env(t_env *e, char **argv);
void				init_object(t_obj *obj);
void				adjust_objects(t_env *env);

void				create_and_run(t_env *e);
void				check_stereo(t_env *e);
void				sdl_help(t_env *env, int x, int y);
t_clr				trace_ray(t_env *env, int rec);
void				init_ray(t_env *env, t_v dest);
void				draw_rt(t_env *env);
int					render(void *environment);
double				closest_intersection(t_env *env, t_surf **closest_surf);
void				save_image(int *mass);

t_clr				light_on(t_env *env, double closest, t_surf *surface,
						int rec);
t_clr				calc_refract(t_env *env, t_lc lc, t_surf *surface, int rec);

void				init_color_variables(t_env *env, t_lc *lc, double closest);
void				calc_color(t_clr *color, double intens, t_surf *surface,
						t_env *env);
void				calc_ref_color(t_clr *color, t_clr *ref_color,
						double reflect);

void				calc_surf_normal(t_env *env, double closest,
						t_surf *surface, t_lc *light);
t_v					calc_reflected_ray(t_v bisect, t_v direction);

int					choose_type(t_env *env, t_lst *surface, double *roots);

int					intersect_paraboloid(t_v *start, t_v *dest, t_surf *parab,
						double *roots);
int					intersect_cylinder(t_v *start, t_v *dest, t_surf *cyl,
						double *roots);
int					intersect_sphere(t_v *start, t_v *dest, t_surf *sph,
						double *roots);
int					intersect_cone(t_v *start, t_v *dest, t_surf *cone,
						double *roots);
int					intersect_plane(t_v *start, t_v *dest, t_surf *plane,
						double *roots);

int					limit_conic(t_surf *surf, t_v *dest, t_v *start,
						double *roots);
int					limit_plane(t_surf *surf, t_v *dest, t_v *start,
						double *roots);
int					limit_sphere(t_surf *surf, t_v *dest, t_v *start,
						double *roots);
int					limit_disc(t_surf *surf, t_v *dest, t_v *start,
						double *roots);

void				calc_basis(t_surf *surf);

void				get_texture_normal(t_surf *surface, t_lc *light);
void				get_texture_color(t_surf *surface, t_lc *light);
void				init_new_color(t_clr *new_color, t_surf *surf, t_env *env);

void				calc_plane_local_coords(t_v *surf_point, t_surf *surface,
						double *u, double *v);
void				calc_sphere_local_coords(t_v *surf_point, t_surf *surface,
						double *u, double *v);
void				calc_conic_local_coords(t_v *surf_p, t_surf *surface,
						double *u, double *v);

void				check_filename(char *file_name);
void				parse_file(char *name, t_env *env);
void				parser_validation(char *name);

void				add_surface(int fd, t_obj *obj);
void				write_field(int fd, char ***split,
						char **line, t_surf *surf);

void				parse_next(int fd, char ***split, char **line);
int					check_floats(char **param, int i);
int					check_param_num(char **param, int i);
void				invalid_syntax(int object);

void				check_empty(char ***split, int object);
int					open_check(int fd, char ***split, char **line);
int					close_check(char ***split, char **line);
int					intensity_check(int fd, char ***split, char **line);
int					texture_check(int fd, char ***split, char **line);
int					color_check(int fd, char ***split, char **line);
int					light_type_check(int fd, char ***split, char **line);
int					surface_type_check(int fd, char ***split, char **line);
int					disruption_check(int fd, char ***split, char **line);

int					check_surface(int fd, char ***split, char **line,
						int *object);
void				validate_surface(int fd, int object);
void				surface_validation(char **split, char *line,
						int object, int fd);

int					check_single_float_field(int fd,
						char ***split, char **line);
int					check_triple_float_field(int fd,
						char ***split, char **line);

void				sepia(t_env *env);
void				blur(t_env *env);
void				stereoscopy(t_env *env);
void				anti_aliasing(t_env *env);
void				save_image(int *mass);
void				cartoon_effect(t_env *env);
void				sum_color(t_clr *aliasing, t_clr *color);
int					check_pixel(t_env *env, int i, int j);
void				stereo_aliasing(t_env *env);

double				*min_root(double *roots);
double				*max_root(double *roots);

t_lst				*list_add(t_lst *lst);
t_lst				*list_create();

#endif
