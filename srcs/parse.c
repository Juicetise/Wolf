/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:46:46 by pdurand           #+#    #+#             */
/*   Updated: 2017/06/21 15:46:48 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	fill_map(t_general *all, char **split, int *x, int y)
{
	int		j;

	j = 0;
	while (split[j] && *x != all->x_nb)
	{
		all->worldmap[y][*x] = ft_atoi(split[j]);
		(*x)++;
		j++;
	}
}

void	gene_map(t_general *all, int x, int y)
{
	char	*line;
	char	**split;
	int		fd;
	int		i;

	split = NULL;
	fd = open("map.txt", O_RDONLY);
	all->worldmap = (int **)malloc(sizeof(int *) * all->y_nb);
	while (get_next_line(fd, &line) == 1 && y != all->y_nb)
	{
		all->worldmap[y] = (int *)malloc(sizeof(int) * all->x_nb);
		split = ft_strsplit(line, ' ');
		if (split)
			fill_map(all, split, &x, y);
		x = 0;
		i = -1;
		while (split[++i])
			free(split[i]);
		free(split);
		ft_strdel(&line);
		y++;
	}
	close(fd);
}

int		wrong_character(char *c)
{
	int i;

	i = 0;
	while (c[i] != '\0')
	{
		if (ft_isdigit(c[i]) == 1 && ft_isdigit(c[i + 1]) == 1)
			return (1);
		if ((c[i] > 47 && c[i] < 55) || c[i] == ' ')
			i++;
		else
			return (1);
	}
	return (0);
}

int		define_xnb(char *line, t_general *all)
{
	int		i;
	int		n;

	n = 0;
	i = 0;
	if (wrong_character(line) == 1)
		free_for_all(all, 3);
	while (line[i])
	{
		if (ft_isdigit(line[i]))
			n++;
		while (line[i] && line[i] != ' ')
			i++;
		while (line[i] && line[i] == ' ')
			i++;
	}
	return (n);
}

void	countxy(t_general *all)
{
	char	*line;
	int		xtmp;
	int		fd;

	fd = open("map.txt", O_RDONLY);
	if (fd == -1)
		free_for_all(all, 1);
	while (get_next_line(fd, &line) == 1)
	{
		all->x_nb = define_xnb(line, all);
		if (all->wit == 0)
		{
			xtmp = all->x_nb;
			all->wit++;
		}
		(all->x_nb != xtmp) ? free_for_all(all, 3) : 1;
		(all->x_nb < 0) ? free_for_all(all, 3) : 1;
		(all->x_nb != 0) ? all->y_nb++ : 1;
		if (line)
			free(line);
	}
	((all->x_nb == 0 || all->y_nb == 0) && fd != -1) ? free_for_all(all, 2) : 1;
	close(fd);
}
