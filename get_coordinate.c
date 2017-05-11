/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 21:06:26 by itsuman           #+#    #+#             */
/*   Updated: 2017/03/29 20:10:59 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char		check_point(int x, int y, t_player *player)
{
	if (player->map[y][x] == 'O' || player->map[y][x] == 'o')
		return ('O');
	else if (player->map[y][x] == 'X' || player->map[y][x] == 'x')
		return ('X');
	return (0);
}

static void	create_matrix(t_player *player)
{
	int	**matrix;
	int	x;
	int y;

	y = 0;
	matrix = (int **)malloc(sizeof(int *) * player->size_map_y);
	while (y < player->size_map_y)
	{
		x = 0;
		matrix[y] = (int *)malloc(sizeof(int) * player->size_map_x);
		while (x < player->size_map_x)
		{
			if (check_point(x + 4, y + 1, player) == player->player_char)
				matrix[y][x] = -1;
			else if (check_point(x + 4, y + 1, player) == player->enemy_char)
				matrix[y][x] = 0;
			else
				matrix[y][x] = -2;
			x++;
		}
		y++;
	}
	player->matrix = matrix;
}

static int	check_matrix_1(t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (y < player->size_map_y)
	{
		x = 0;
		while (x < player->size_map_x)
		{
			if (player->matrix[y][x] == -2)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static void	fill_matrix(t_player *player, int **m, int i, int j)
{
	int x;
	int y;

	y = 0;
	while (y < player->size_map_y)
	{
		x = -1;
		while (++x < player->size_map_x)
			if (m[y][x] == i)
			{
				if (y - 1 != -1 && m[y - 1][x] != -1 && m[y - 1][x] != 0 &&
						m[y - 1][x] == -2)
					m[y - 1][x] = j;
				if (y + 1 < player->size_map_y && m[y + 1][x] != -1 &&
						m[y + 1][x] != 0 && m[y + 1][x] == -2)
					m[y + 1][x] = j;
				if (x - 1 != -1 && m[y][x - 1] != -1 && m[y][x - 1] != 0 &&
						m[y][x - 1] == -2)
					m[y][x - 1] = j;
				if (x + 1 < player->size_map_x && m[y][x + 1] != -1 &&
						m[y][x + 1] != 0 && m[y][x + 1] == -2)
					m[y][x + 1] = j;
			}
		y++;
	}
}

void		get_coordinate(t_player *player, t_place **start)
{
	int	i;
	int j;

	i = 0;
	j = 1;
	create_matrix(player);
	while (check_matrix_1(player) && check_matrix_2(player, player->matrix, i))
	{
		fill_matrix(player, player->matrix, i, j);
		i++;
		j++;
	}
	fill_coordinate(player, start);
}
