/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpardini <gpardini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:13:11 by gpardini          #+#    #+#             */
/*   Updated: 2024/02/27 12:47:56 by gpardini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "./minilibx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_data
{
    char *map_NO;
    char *map_SO;
    char *map_WE;
    char *map_EA;
    char *map_F;
    char *map_C;
    int  map_x;
    int  map_y;
    char **map;
    //parte para contar PCE flood_fill
    double player_x;
    double player_y;
    double player_a;
    char   player_d;
}	t_data;

typedef struct s_game
{
    void *mlx;
    void *mlx_win;
}	t_game;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

t_data	*data(void);
//get_next_line utils
int	    ound_breakline(char *string);
char	*bl_strjoin(char *line, char *add);
char	*seek_line(int fd, char *buffer);
void	over_read(char *buffer);
char	*get_next_line(int fd);
//lib utils
int	ft_strcmp(char *s1, char *s2);
int	ft_strlen(const char *str);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
//utils from so_long
void	map_put_image(void);
//render.c functions
void render_this_shit(t_img *img);

#endif