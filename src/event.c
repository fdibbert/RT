/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 05:21:02 by emayert           #+#    #+#             */
/*   Updated: 2019/04/17 19:38:57 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void	mouse_click_supply(t_env *e, t_obj *obj)
{
	e->gui->selected_object_type = GUI_SELECTED_TYPE_OBJ;
	if (e->gui->selected_object == (t_obj *)obj)
		e->gui->win_info.visible ^= 1;
	else
	{
		e->gui->selected_object = (t_obj *)obj;
		e->gui->win_info.visible = 1;
	}
	e->gui->need_update_info = 1;
	draw_all(e);
}

static	void	mouse_click(SDL_Event *event, t_env *e)
{
	SDL_Rect	rect;
	t_obj		*obj;
	t_v			dest;
	t_v			p;
	double		close_dist;

	rect = (SDL_Rect) {GUI_LBLOCK_W + kiss_edge, kiss_edge, RT__W, RT__H};
	if (kiss_pointinrect(event->button.x, event->button.y, &rect))
	{
		p.x = (event->button.x - e->constants.half_render_w - GUI_LBLOCK_W) /
																(double)RT__W;
		p.y = -(event->button.y - e->constants.half_render_h) / (double)RT__H;
		dest = (t_v){p.x, p.y, 1.0};
		dest = vecnorm(vec_rotate(e->cam.rotation, dest));
		init_ray(e, dest);
		get_obj_by_click(e, &obj, &close_dist, e->objects);
		if (close_dist < e->ray.max)
			mouse_click_supply(e, obj);
	}
}

void			events_handler(SDL_Event *event, t_env *env)
{
	if (event->type == SDL_MOUSEBUTTONDOWN)
		mouse_click(event, env);
	else if (event->type == SDL_KEYDOWN)
		sdl_key_press_events(event, env);
}
