/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 17:41:16 by pdurand           #+#    #+#             */
/*   Updated: 2017/06/24 17:41:18 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int		handle_events_a(t_general *all)
{
	int		act;

	act = 0;
	if (all->key[SDL_SCANCODE_UP] == 1)
	{
		if (all->worldmap[(int)(all->posx + all->dirx * D_PAS)]\
			[(int)all->posy] == 0)
			all->posx += all->dirx * D_PAS;
		if (all->worldmap[(int)all->posx]\
			[(int)(all->posy + all->diry * D_PAS)] == 0)
			all->posy += all->diry * D_PAS;
		act = 1;
	}
	if (all->key[SDL_SCANCODE_DOWN] == 1)
	{
		if (all->worldmap[(int)(all->posx - all->dirx * D_PAS)]\
			[(int)all->posy] == 0)
			all->posx -= all->dirx * D_PAS;
		if (all->worldmap[(int)all->posx]\
			[(int)(all->posy - all->diry * D_PAS)] == 0)
			all->posy -= all->diry * D_PAS;
		act = 1;
	}
	return (act);
}

static int		handle_events_c(t_general *all)
{
	int		act;

	act = 0;
	if (all->key[SDL_SCANCODE_RIGHT] == 1)
	{
		all->olddirx = all->dirx;
		all->dirx = all->dirx * cos(-R_PAS) - all->diry * sin(-R_PAS);
		all->diry = all->olddirx * sin(-R_PAS) + all->diry * cos(-R_PAS);
		all->oldplanex = all->planex;
		all->planex = all->planex * cos(-R_PAS) - all->planey * sin(-R_PAS);
		all->planey = all->oldplanex * sin(-R_PAS) + all->planey * cos(-R_PAS);
		act = 1;
	}
	return (act);
}

int				handle_events(t_general *all)
{
	int		act;

	act = 0;
	act += handle_events_a(all);
	act += handle_events_c(all);
	if (all->key[SDL_SCANCODE_LEFT] == 1)
	{
		all->olddirx = all->dirx;
		all->dirx = all->dirx * cos(R_PAS) - all->diry * sin(R_PAS);
		all->diry = all->olddirx * sin(R_PAS) + all->diry * cos(R_PAS);
		all->oldplanex = all->planex;
		all->planex = all->planex * cos(R_PAS) - all->planey * sin(R_PAS);
		all->planey = all->oldplanex * sin(R_PAS) + all->planey * cos(R_PAS);
		act = 1;
	}
	return ((act > 0 ? 1 : 0));
}
