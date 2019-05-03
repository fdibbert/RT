/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 20:14:01 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/15 16:32:04 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_lst	*list_create(void)
{
	t_lst	*new;

	new = (t_lst *)malloc(sizeof(t_lst));
	new->id = 0;
	new->type = -2;
	new->next = NULL;
	new->obj = NULL;
	return (new);
}

t_lst	*list_add(t_lst *lst)
{
	t_lst	*new;

	new = (t_lst *)malloc(sizeof(t_lst));
	while (lst->next)
		lst = lst->next;
	lst->next = new;
	new->id = lst->id + 1;
	new->type = -1;
	new->obj = NULL;
	new->next = NULL;
	return (new);
}
