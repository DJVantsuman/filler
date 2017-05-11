/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 16:16:18 by itsuman           #+#    #+#             */
/*   Updated: 2017/03/30 18:22:16 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	get_player_number(char *line, t_player *player)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (line[i] != 'p')
		i++;
	n = ft_atoi(ft_strsub(line + ++i, 0, 1));
	player->player_char = n == 1 ? 'O' : 'X';
	player->enemy_char = player->player_char == 'O' ? 'X' : 'O';
}

static void	get_size_map(char *line, t_player *player, int f)
{
	int		i;
	char	*s;

	i = 0;
	s = "";
	while (line[i] != ' ')
		i++;
	if (f == 1)
	{
		player->size_map_y = ft_atoi(line + ++i);
		while (line[i] != ' ')
			i++;
		player->size_map_x = ft_atoi(line + ++i);
	}
	else if (f == 2)
		player->size_piece_y = ft_atoi(line + ++i);
}

static void	fill_map(int fd, t_player *player)
{
	int		y;
	int		i;
	char	*line;

	y = player->size_map_y + 1;
	i = 0;
	line = NULL;
	player->map = (char **)malloc(sizeof(char *) *
			(player->size_map_y + 2));
	while (y > 0)
	{
		get_next_line(fd, &line);
		player->map[i] = ft_strjoin(line, "\0");
		y--;
		i++;
		ft_strdel(&line);
	}
}

static void	fill_piece(int fd, t_player *player)
{
	int		y;
	int		i;
	char	*line;

	y = player->size_piece_y;
	i = 0;
	player->piece = (char **)malloc(sizeof(char *) *
			(player->size_piece_y + 1));
	while (y > 0)
	{
		get_next_line(fd, &line);
		player->piece[i] = ft_strjoin(line, "\0");
		y--;
		i++;
		ft_strdel(&line);
	}
	y = 0;
	while (player->piece[0][y] != '\0')
		y++;
	player->size_piece_x = y;
}

int			main(void)
{
	t_player	player;
	t_place		*start;
	char		*line;

	start = (t_place *)malloc(sizeof(t_place) + 1);
	while (get_next_line(0, &line))
	{
		if (player.player_char == 0)
		{
			while (ft_strstr(line, "filler") == NULL)
				get_next_line(0, &line);
			get_player_number(line, &player);
		}
		while (ft_strstr(line, "Plateau") == 0)
			get_next_line(0, &line);
		get_size_map(line, &player, 1);
		fill_map(0, &player);
		get_next_line(0, &line);
		get_size_map(line, &player, 2);
		fill_piece(0, &player);
		get_coordinate(&player, &start);
		free(player.map);
		free(player.piece);
	}
	return (0);
}
