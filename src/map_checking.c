/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afantini <afantini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:12:26 by luigi             #+#    #+#             */
/*   Updated: 2024/06/28 16:22:07 by afantini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../build/inc/cub3d.h"

static bool	check_map_blank(t_game *game, int i, int j)
{
	if (game->map[i + 1][j] && game->map[i + 1][j] != ' ')
	{
		if (game->map[i - 1][j] && game->map[i - 1][j] != ' ')
			return (SUCCESS);
	}
	return (FAILURE);
}

bool	check_map_wall(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->y)
	{
		j = -1;
		if (i == 0 || i == game->y - 1)
		{
			while (++j < ft_strlen(game->map[i]))
			{
				if (!(game->map[i][j] == '1' || game->map[i][j] == ' '))
					return (FAILURE);
			}
		}
		else
		{
			while (game->map[i][++j] == ' ')
				;
			if (!(game->map[i][j] == '1'
				&& game->map[i][ft_strlen(game->map[i]) - 1] == '1'))
				return (FAILURE);
		}
	}
	return (SUCCESS);
}

// 0.77 --> 45 gradi; p++ --> posizioni del giocatore nella mappa
void	map_player(t_game *game, int i, int j)
{
	game->player->pos_x = j + 0.5;
	game->player->pos_y = i + 0.5;
	if (game->map[i][j] == 'N')
	{
		game->player->dir_y = -1;
		game->player->plane_x = 0.77;
	}
	else if (game->map[i][j] == 'S')
	{
		game->player->dir_y = 1;
		game->player->plane_x = -0.77;
	}
	else if (game->map[i][j] == 'W')
	{
		game->player->dir_x = -1;
		game->player->plane_y = -0.77;
	}
	else if (game->map[i][j] == 'E')
	{
		game->player->dir_x = 1;
		game->player->plane_y = 0.77;
	}
	game->pl_pos_cnt++;
	return ;
}

static void	check_cell(t_game *game, int i, int j)
{
	if (game->map[i][j] == '0' || game->map[i][j] == 'N'
		|| game->map[i][j] == 'S' || game->map[i][j] == 'E'
		|| game->map[i][j] == 'W')
	{
		if (check_map_blank(game, i, j))
			write_error_n_exit(1, "Error:\nMap is open/invalid\n", NULL, game);
	}
	if (game->map[i][j] != '0' && game->map[i][j] != '1'
		&& game->map[i][j] != ' ')
	{
		if (game->map[i][j] != 'N' && game->map[i][j] != 'S'
				&& game->map[i][j] != 'E' && game->map[i][j] != 'W')
			write_error_n_exit(1, "Error:\nContents error\n", NULL, game);
		map_player(game, i, j);
	}
}

int	check_map_contents(t_game *game)
{
	int	i;
	int	j;
	int	max_j;

	i = -1;
	max_j = 100;
	while (++i < game->y)
	{
		j = -1;
		while (++j < ft_strlen(game->map[i]))
			check_cell(game, i, j);
		if (max_j > j)
			max_j = j;
	}
	if (game->y < 4 && max_j < 4)
		write_error_n_exit(1, "Error:\nMap is too small\n", NULL, game);
	return (0);
}
