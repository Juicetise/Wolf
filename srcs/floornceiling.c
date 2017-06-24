/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floornceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 18:28:14 by pdurand           #+#    #+#             */
/*   Updated: 2017/06/24 18:28:16 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	calculate_floor(t_th_wolf *unth)
{
	if (unth->side == 0 && unth->raydirx > 0)
	{
		unth->floorxwall = unth->mapx;
		unth->floorywall = unth->mapy + unth->wallx;
	}
	else if (unth->side == 0 && unth->raydirx < 0)
	{
		unth->floorxwall = unth->mapx + 1.0;
		unth->floorywall = unth->mapy + unth->wallx;
	}
	else if (unth->side == 1 && unth->raydiry > 0)
	{
		unth->floorxwall = unth->mapx + unth->wallx;
		unth->floorywall = unth->mapy;
	}
	else if (unth->side == 1 && unth->raydiry < 0)
	{
		unth->floorxwall = unth->mapx + unth->wallx;
		unth->floorywall = unth->mapy + 1.0;
	}
}

void	drawfloor(int x, t_general *all, t_th_wolf *unth)
{
	int checkerboardpattern;
	int y;

	unth->distwall = unth->perpwalldist;
	unth->distplayer = 0;
	y = unth->drawend;
	while (y <= all->height)
	{
		unth->currentdist = (double)all->height /\
		(2 * (double)y - (double)all->height);
		unth->weight = (unth->currentdist - unth->distplayer) /\
		(unth->distwall - unth->distplayer);
		unth->currentfloorx = unth->weight * unth->floorxwall +\
		(1.0 - unth->weight) * unth->posx;
		unth->currentfloory = unth->weight * unth->floorywall +\
		(1.0 - unth->weight) * unth->posy;
		unth->floortexx = (int)(unth->currentfloorx * 512) % 512;
		unth->floortexy = (int)(unth->currentfloory * 512) % 512;
		checkerboardpattern = ((int)(unth->currentfloorx +\
		unth->currentfloory)) % 2;
		define_color2(all, unth);
		pxl2img(all, x, y, unth->colorfloor);
		pxl2img(all, x, all->height - y, unth->colortop);
		y++;
	}
}

void	define_color2(t_general *all, t_th_wolf *unth)
{
	unth->colorfloor = get_pixel(all->floor, unth->floortexx,\
	(unth->floortexy));
	unth->colortop = get_pixel(all->ceiling, unth->floortexx,\
	(unth->floortexy));
}
