/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afantini <afantini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:11:52 by luigi             #+#    #+#             */
/*   Updated: 2024/06/28 16:16:20 by afantini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../build/inc/cub3d.h"

static void	initialize_struct(t_game *game)
{
	memset(game, 0, sizeof(t_game));
	game->ceiling = -1;
	game->floor = -1;
	return ;
}

// le altre inizializzazioni a 0 sono ridondanti
static void	initialize_player(t_game *game)
{
	game->pl_pos_cnt = 0;
	game->player = ft_calloc(sizeof(t_player), 1);
	if (!game->player)
		write_error_n_exit(1, "Error:\nCalloc_player failed.\n", NULL, game);
	return ;
}

void	initialize_data(t_game *game)
{
	int	i;

	initialize_struct(game);
	game->wall = (int **)ft_calloc(sizeof(int *) * 4, 1);
	if (!game->wall)
		write_error_n_exit(1, "Error:\nCalloc_data failed.\n", NULL, game);
	i = -1;
	while (++i < 4)
	{
		game->wall[i] = (int *)ft_calloc(sizeof(int) \
				* (TEX_SIZE * TEX_SIZE), 1);
		if (!game->wall[i])
			write_error_n_exit(1, "Error:\nCalloc_wall_arr failed.\n",
				NULL, game);
	}
	initialize_player(game);
	return ;
}

void	initialize_game_env(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, "cub3d");
	game->texture.image = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	game->texture.addr = (int *)mlx_get_data_addr(game->texture.image,
			&game->texture.bits_per_pixel, &game->texture.line_length,
			&game->texture.endian);
	return ;
}

void	initialize_map(t_game *game, int fd)
{
	char	*tmp;

	tmp = read_map_lines(game, fd);
	if (!tmp[0])
	{
		free(tmp);
		write(1, "Error:\nEmpty map", 17);
		exit(1);
	}
	game->cub = ft_split(tmp, '\n');
	free(tmp);
	close(fd);
}
