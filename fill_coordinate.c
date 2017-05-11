/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_coordinate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 18:22:07 by itsuman           #+#    #+#             */
/*   Updated: 2017/03/29 20:12:55 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			check_matrix_2(t_player *player, int **m, int num)
{
	int	x;
	int	y;

	y = 0;
	while (y < player->size_map_y)
	{
		x = 0;
		while (x < player->size_map_x)
		{
			if (m[y][x] == num)
			{
				if (y - 1 != -1 && m[y - 1][x] == -2)
					return (1);
				else if (y + 1 < player->size_map_y && m[y + 1][x] == -2)
					return (1);
				else if (x - 1 != -1 && m[y][x - 1] == -2)
					return (1);
				else if (x + 1 < player->size_map_x && m[y][x + 1] == -2)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

static	int	check_place(int x_map, int y_map, t_player *player, int count)
{
	int x_p;
	int y_p;
	int x_map_const;

	y_p = -1;
	x_map_const = x_map;
	if (x_map + player->size_piece_x < player->size_map_x + 4 &&
			y_map + player->size_piece_y < player->size_map_y + 1)
		while (++y_p < player->size_piece_y)
		{
			x_p = -1;
			x_map = x_map_const - 1;
			while (++x_p < player->size_piece_x && ++x_map >= 0)
				if (player->piece[y_p][x_p] == '*' &&
						player->map[y_map][x_map] == player->player_char)
					count++;
				else if (player->piece[y_p][x_p] == '*' &&
						player->map[y_map][x_map] == player->enemy_char)
					return (0);
			y_map++;
		}
	if (count == 1)
		return (1);
	return (0);
}

static void	get_priority(t_player *player, t_place **start, int x, int y)
{
	int			x_piece;
	int			y_piece;
	t_place		*p;
	t_place		*var_place;

	p = (t_place *)malloc(sizeof(t_place));
	x_piece = 0;
	y_piece = 0;
	p->x = x;
	p->y = y;
	p->priority = 0;
	var_place = *start;
	while (y_piece < player->size_piece_y)
	{
		x_piece = 0;
		while (x_piece < player->size_piece_x)
		{
			if (player->piece[y_piece][x_piece] == '*')
				p->priority += player->matrix[y + y_piece][x + x_piece];
			x_piece++;
		}
		y_piece++;
	}
	p->next = var_place;
	*start = p;
}

static void	write_coordinate(t_place **start)
{
	t_place place;
	t_place *var_start;

	place.priority = 99999999;
	while ((*start)->next != NULL)
	{
		var_start = (*start);
		while (var_start->next != NULL)
		{
			if (var_start->priority < place.priority)
			{
				place.x = var_start->x;
				place.y = var_start->y;
				place.priority = var_start->priority;
			}
			var_start = var_start->next;
		}
		(*start) = (*start)->next;
	}
	ft_putnbr_fd(place.y, 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(place.x, 1);
	ft_putchar_fd('\n', 1);
}

void		fill_coordinate(t_player *player, t_place **start)
{
	int		x;
	int		y;

	y = 1;
	(*start)->priority = 99999999;
	(*start)->next = NULL;
	while (y < player->size_map_y + 1)
	{
		x = 4;
		while (x < player->size_map_x + 4)
		{
			if (check_place(x, y, player, 0))
				get_priority(player, start, x - 4, y - 1);
			x++;
		}
		y++;
	}
	write_coordinate(start);
}
