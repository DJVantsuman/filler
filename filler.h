/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 16:17:56 by itsuman           #+#    #+#             */
/*   Updated: 2017/03/29 20:15:25 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FILLER_H
# define _FILLER_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct		s_filler
{
	char			**map;
	char			**piece;
	char			player_char;
	char			enemy_char;
	int				**matrix;
	int				size_map_x;
	int				size_map_y;
	int				size_piece_x;
	int				size_piece_y;
	int				x;
	int				y;
}					t_player;

typedef struct		s_place
{
	int				x;
	int				y;
	int				priority;
	struct s_place	*next;
}					t_place;

int					get_next_line(const int fd, char **line);
int					check_matrix_2(t_player *player, int **matrix, int num);
char				check_point(int x, int y, t_player *player);
void				get_coordinate(t_player *player, t_place **start);
void				fill_coordinate(t_player *player, t_place **start);

#endif
