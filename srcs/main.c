/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:08:17 by pdurand           #+#    #+#             */
/*   Updated: 2017/06/07 17:08:18 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		free_for_all(t_general *all, int x)
{
	if (x == 1)
		write(1, "map.txt is missing\n", 19);
	if (x == 2)
		write(1, "error : empty map\n", 19);
	if (x == 3)
		write(1, "wrong map format\n", 17);
	free(all);
	SDL_DestroyWindow(all->wn);
	SDL_DestroyTexture(all->texture);
	exit(1);
}

static int	global_loop(t_general *all)
{
	while (all->run)
	{
		SDL_PollEvent(&all->event);
		if (all->event.type == 256)
			all->run = 0;
		if (all->event.window.type == SDL_WINDOWEVENT_CLOSE
			|| all->event.key.keysym.sym == SDLK_ESCAPE
			|| all->event.type == SDL_QUIT)
			all->run = 0;
		handle_events(all);
		threaded_render(all);
		SDL_UpdateWindowSurface(all->wn);
		all->key = SDL_GetKeyboardState(NULL);
	}
	free_for_all(all, 0);
	return (0);
}

int			main(int argc, char **argv)
{
	char **useless;
	t_general	*all;

	useless = argv;
	if (argc == 1)
	{
		all = (t_general *)malloc(sizeof(t_general));
		init(all);
		init_sdl(all);
		init_textures(all);
		global_loop(all);
	}
	return (0);
}
