/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 18:30:50 by pdurand           #+#    #+#             */
/*   Updated: 2017/06/24 18:30:51 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			draw_wolf(t_general *all, int x, t_th_wolf *unth)
{
	init_wolf(all, x, unth);
	calculate_pos(unth);
	calculate_ray(unth, all);
	calculate_wall(all, unth);
	unth->texnum = all->worldmap[unth->mapx][unth->mapy];
	drawline(x, all, unth);
	calculate_floor(unth);
	drawfloor(x, all, unth);
}

static void		process_wolf(t_general *all, int part, t_th_wolf *unth)
{
	register int		x;
	int					start;
	int					stop;

	unth->i = unth->i;
	start = (all->height / THREADS) * part;
	stop = (all->height / THREADS) * (part + 1);
	x = start;
	while (x < stop)
	{
		draw_wolf(all, x, unth);
		x++;
	}
}

static void		*threaderize_wolf(void *th)
{
	t_th_wolf			*unth;

	unth = (t_th_wolf *)th;
	process_wolf(unth->all, unth->part, unth);
	pthread_exit(NULL);
}

int				threaded_render(t_general *all)
{
	pthread_t			tid[THREADS];
	t_th_wolf			f_threads[THREADS];
	register int		i;

	i = 0;
	while (i < THREADS)
	{
		f_threads[i].all = all;
		f_threads[i].part = i;
		pthread_create(&tid[i], NULL, threaderize_wolf, &f_threads[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(tid[i++], NULL);
	return (0);
}
