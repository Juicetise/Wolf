/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 18:41:55 by pdurand           #+#    #+#             */
/*   Updated: 2017/06/24 18:41:56 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	init(t_general *all)
{
	countxy(all);
	gene_map(all, 0, 0);
	clear_map(all);
	write(1, "Quest : try to find HAL 9000 to return to earth\n", 49);
	all->test = 0;
	all->run = 1;
	all->t_w = 512;
	all->t_h = 512;
	all->topcolor = 0x00CCEEFF;
	all->floorcolor = 0x00A87658;
	all->hit = 0;
	all->posx = 2;
	all->posy = 2;
	all->dirx = -1;
	all->diry = 0;
	all->planex = 0;
	all->planey = 0.66;
	all->color = 0x00859595;
	all->height = 1000;
	all->width = 1000;
	if (!(all->key = SDL_GetKeyboardState(NULL)))
		return ;
}

void	clear_map(t_general *all)
{
	if (all->worldmap[2][2] != 0)
		all->worldmap[2][2] = 0;
	if (all->worldmap[1][1] != 0)
		all->worldmap[1][1] = 0;
	if (all->worldmap[2][1] != 0)
		all->worldmap[2][1] = 0;
	if (all->worldmap[1][2] != 0)
		all->worldmap[1][2] = 0;
}

int		init_sdl(t_general *all)
{
	if (SDL_Init(SDL_INIT_EVENTS) == -1)
		return (0);
	if (!(all->wn =\
	SDL_CreateWindow("Wolf3D", 0, 0, all->width, all->height, 0)))
		return (0);
	all->pixels = SDL_GetWindowSurface(all->wn)->pixels;
	return (1);
}

void	init_textures(t_general *all)
{
	all->wall_window = SDL_LoadBMP("texture/window.bmp");
	all->wall_t1 = SDL_LoadBMP("texture/alienwall2.bmp");
	all->wall_optical = SDL_LoadBMP("texture/optical2.bmp");
	all->wall_optic = SDL_LoadBMP("texture/optical1.bmp");
	all->wall_hal = SDL_LoadBMP("texture/HAL.bmp");
	all->floor = SDL_LoadBMP("texture/brdrlndsfloor.bmp");
	all->ceiling = SDL_LoadBMP("texture/alienwall.bmp");
	all->meme = SDL_LoadBMP("texture/memxp.bmp");
}

void	init_wolf(t_general *all, int x, t_th_wolf *unth)
{
	unth->distplayer = 0;
	unth->color = all->color;
	unth->perpwalldist = 0;
	unth->hit = all->hit;
	unth->posx = all->posx;
	unth->posy = all->posy;
	unth->dirx = all->dirx;
	unth->diry = all->diry;
	unth->planex = all->planex;
	unth->planey = all->planey;
	unth->camerax = 2 * x / (double)all->width - 1;
	unth->rayposx = unth->posx;
	unth->rayposy = unth->posy;
	unth->raydirx = unth->dirx + unth->planex * unth->camerax;
	unth->raydiry = unth->diry + unth->planey * unth->camerax;
	unth->mapx = (int)unth->rayposx;
	unth->mapy = (int)unth->rayposy;
	unth->deltadistx = sqrt(1 + (unth->raydiry * unth->raydiry) /\
							(unth->raydirx * unth->raydirx));
	unth->deltadisty = sqrt(1 + (unth->raydirx * unth->raydirx) /\
							(unth->raydiry * unth->raydiry));
}
