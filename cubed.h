/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpardini <gpardini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:13:11 by gpardini          #+#    #+#             */
/*   Updated: 2024/02/06 12:13:46 by gpardini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "./minilibx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_data
{
    char *map_NO;
    char *map_SO;
    char *map_WE;
    char *map_EA;
    char *map_F;
    char *map_C;
    char **map;
    //:D
}	t_data;

//get_next_line utils
int	    ound_breakline(char *string);
char	*bl_strjoin(char *line, char *add);
char	*seek_line(int fd, char *buffer);
void	over_read(char *buffer);
char	*get_next_line(int fd);
//lib utils
int	ft_strcmp(char *s1, char *s2);
int	ft_strlen(const char *str);

#endif