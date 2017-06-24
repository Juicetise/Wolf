/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 18:34:01 by pdurand           #+#    #+#             */
/*   Updated: 2017/06/24 18:34:02 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

Uint32	get_pixel(SDL_Surface *surface, int x, int y)
{
	Uint8 *p;

	p = (Uint8 *)surface->pixels + (int)y * surface->pitch +\
	(int)x * surface->format->BytesPerPixel;
	if (surface->format->BytesPerPixel == 1)
		return (*p);
	if (surface->format->BytesPerPixel == 2)
		return (*(Uint16 *)p);
	if (surface->format->BytesPerPixel == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	}
	if (surface->format->BytesPerPixel == 4)
		return (*(Uint32 *)p);
	else
		return (0);
}

void	pxl2img(t_general *all, int x, int y, int color)
{
	all->pixels[(int)(all->width) * y + x] = color;
}

void	write_end(t_general *all)
{
	write(1, "Hello, HAL. Do you read me, HAL?\n", 34);
	write(1, "Affirmative, Dave. I read you.\n", 31);
	write(1, "Hal, can you iniate our way back to Earth?\n", 43);
	write(1, "I'm sorry, Dave. I'm afraid I can't do that.\n", 46);
	all->test = 1;
}
