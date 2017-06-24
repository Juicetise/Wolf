/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 18:46:01 by pdurand           #+#    #+#             */
/*   Updated: 2017/06/24 18:46:02 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	calculate_pos(t_th_wolf *unth)
{
	if (unth->raydirx < 0)
	{
		unth->stepx = -1;
		unth->sidedistx = (unth->rayposx - unth->mapx) * unth->deltadistx;
	}
	else
	{
		unth->stepx = 1;
		unth->sidedistx = (unth->mapx + 1.0 - unth->rayposx) * unth->deltadistx;
	}
	if (unth->raydiry < 0)
	{
		unth->stepy = -1;
		unth->sidedisty = (unth->rayposy - unth->mapy) * unth->deltadisty;
	}
	else
	{
		unth->stepy = 1;
		unth->sidedisty = (unth->mapy + 1.0 - unth->rayposy) * unth->deltadisty;
	}
}

void	calculate_ray(t_th_wolf *unth, t_general *all)
{
	while (unth->hit == 0)
	{
		if (unth->sidedistx < unth->sidedisty)
		{
			unth->sidedistx += unth->deltadistx;
			unth->mapx += unth->stepx;
			unth->side = 0;
		}
		else
		{
			unth->sidedisty += unth->deltadisty;
			unth->mapy += unth->stepy;
			unth->side = 1;
		}
		if (all->worldmap[unth->mapx][unth->mapy] > 0)
			unth->hit = 1;
	}
}

void	calculate_wall(t_general *all, t_th_wolf *unth)
{
	if (unth->side == 0)
		unth->perpwalldist = (unth->mapx - unth->rayposx\
							+ (1.0 - unth->stepx) / 2.0) / unth->raydirx;
	else
		unth->perpwalldist = (unth->mapy - unth->rayposy\
							+ (1.0 - unth->stepy) / 2.0) / unth->raydiry;
	unth->lineheight = ((int)(all->height / unth->perpwalldist));
	unth->drawstart = -unth->lineheight / 2.0 + all->height / 2.0;
	if (unth->drawstart < 0)
		unth->drawstart = 0;
	unth->drawend = unth->lineheight / 2.0 + all->height / 2.0;
	if (unth->drawend >= all->height)
		unth->drawend = all->height;
	if (unth->side == 0)
		unth->wallx = unth->rayposy + unth->perpwalldist * unth->raydiry;
	else
		unth->wallx = unth->rayposx + unth->perpwalldist * unth->raydirx;
	unth->wallx -= (int)unth->wallx;
	unth->tex_x = (int)(unth->wallx * (double)all->t_w);
	if (unth->side == 0 && unth->raydirx > 0)
		unth->tex_x = all->t_w - unth->tex_x - 1;
	if (unth->side == 1 && unth->raydiry < 0)
		unth->tex_x = all->t_w - unth->tex_x - 1;
}

void	drawline(int x, t_general *all, t_th_wolf *unth)
{
	while (unth->drawstart <= unth->drawend)
	{
		unth->d = unth->drawstart * 512 - all->height\
		* 256 + unth->lineheight * 256;
		unth->tex_y = ((unth->d * all->t_h) /\
		unth->lineheight) / 512;
		if (unth->texnum == 1)
			unth->color = get_pixel(all->wall_t1, unth->tex_x, (unth->tex_y));
		if (unth->texnum == 2)
			unth->color =
			get_pixel(all->wall_window, unth->tex_x, (unth->tex_y));
		if (unth->texnum >= 3 && unth->texnum <= 6)
			define_color(all, unth);
		if (unth->side == 1)
			unth->color = (unth->color >> 1) & 8355711;
		pxl2img(all, x, unth->drawstart, unth->color);
		unth->drawstart++;
	}
}

void	define_color(t_general *all, t_th_wolf *unth)
{
	int	g;
	
	g = 0;
	if (unth->texnum == 3)
	{
		unth->color = get_pixel(all->wall_hal, unth->tex_x, (unth->tex_y));
		if (all->test == 0)
			write_end(all);
	}
	if (unth->texnum == 4)
		unth->color = get_pixel(all->wall_optical, unth->tex_x, (unth->tex_y));
	if (unth->texnum == 5)
		unth->color = get_pixel(all->wall_optic, unth->tex_x, (unth->tex_y));
	if (unth->texnum == 6)
		unth->color = get_pixel(all->meme, unth->tex_x, (unth->tex_y));
}
