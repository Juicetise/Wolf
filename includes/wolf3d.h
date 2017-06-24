/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf0d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdurand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:08:11 by pdurand           #+#    #+#             */
/*   Updated: 2017/06/07 17:08:12 by pdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <math.h>
# include "../frameworks/SDL2.framework/Headers/SDL.h"
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define D_PAS		0.03
# define R_PAS		0.03
# define mapWidth 24
# define mapHeight 24
# define THREADS 8
# define texwidth 64
# define texheight 64

typedef struct		s_general
{
	int				height;
	int				width;
	void			*mx;
	SDL_Window		*wn;
	void			*img;
	char			*argv;
	int				bpp;
	int				len;
	int				endian;
	char			*data;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			camerax;
	double			rayposx;
	double			rayposy;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double sidedistx;
	double sidedisty;
	double deltadistx;
	double deltadisty;
	double perpwalldist;
	int		stepx;
	int		stepy;
	int hit;
	int	side;
	int	lineheight;
	int	drawstart;
	int drawend;
	int color;
	int		hittmp;;
	double posxtmp;
	double posytmp;
	double dirxtmp;
	double dirytmp;
	double planextmp;
	double planeytmp;
	double olddirx;
	double oldplanex;
	int		topcolor;
	int		floorcolor;
	SDL_RWops *rwop;
	SDL_Surface *wall_t1;
	SDL_Surface	*wall_optic;
	SDL_Surface *wall_optical;
	SDL_Surface	*wall_hal;
	SDL_Surface	*wall_window;
	SDL_Surface *floor;
	SDL_Surface *ceiling;
	SDL_Surface *meme;
	int		t_h;
	int		t_w;
	SDL_Texture		*texture;
	int				*pixels;
	const Uint8		*key;
	char	run;
	SDL_Event		event;
	int				test;
	int				**worldmap;
	int				y_nb;
	int				x_nb;
	int				wit;
}					t_general;

typedef struct		s_th_wolf
{
	int				mapx;
	int				mapy;
	double sidedistx;
	double sidedisty;
	double deltadistx;
	double deltadisty;
	double perpwalldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	double			camerax;
	double			rayposx;
	double			rayposy;
	double			raydirx;
	double			raydiry;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			i;
	t_general		*all;
	int				part;
	unsigned int			color;
	int	tex_x;
	int	tex_y;
	double wallx;
	int	d;
	int	texnum;
	double time;
	double oldtime;
	double fps;
	double movespeed;
	double rotspeed;
	double weight;
	double currentfloorx;
	double currentfloory;
	int floortexy;
	int floortexx;
	double floorxwall;
	double floorywall;
	double distwall;
	double distplayer;
	double currentdist;
	int		colorfloor;
	int		colortop;
}					t_th_wolf;

void	drawline(int x, t_general *all, t_th_wolf *unth);
void	pxl2img(t_general *all, int x, int y, int color);
int		clear_image(t_general *all, int x, int y);
int		expose_wolf(t_general *all);
int		ft_close(t_general *all);
void	draw_wolf(t_general *all, int x, t_th_wolf *unth);
void	init_wolf(t_general *all, int x, t_th_wolf *unth);
void	calculate_pos(t_th_wolf *unth);
void	calculate_ray(t_th_wolf *unth, t_general *all);
void	calculate_wall(t_general *all, t_th_wolf *unth);
int				threaded_render(t_general *all);
void	draw_tex(t_general *all);
Uint32		get_pixel(SDL_Surface *src, int x, int y);
void	drawfloor(int x, t_general *all, t_th_wolf *unth);
void	calculate_floor(t_th_wolf *unth);
void	drawfloor2(int x, t_general *all, t_th_wolf *unth);
int				handle_events(t_general *all);
void	init(t_general *all);
int			init_sdl(t_general *all);
void	init_textures(t_general *all);
void	gene_map(t_general *all, int x, int y);
void	fill_map(t_general *all, char **split, int *x, int y);
void	printmap(t_general *all);
void	clear_map(t_general *all);
void	write_end(t_general *all);
int		wrong_character(char *c);
int		define_xnb(char *line, t_general *all);
void	countxy(t_general *all);
void		free_for_all(t_general *all, int x);
void	define_color(t_general *all, t_th_wolf *unth);
void	define_color2(t_general *all, t_th_wolf *unth);

#endif
