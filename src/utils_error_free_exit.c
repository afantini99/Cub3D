/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error_free_exit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afantini <afantini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:11:40 by luigi             #+#    #+#             */
/*   Updated: 2024/06/21 16:51:23 by afantini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../build/inc/cub3d.h"

// STDOUT_FILENO: si sta scrivendo sul flusso di output standard del processo.
void	write_error_n_exit(int err, char *msg, char *str, t_game *game)
{
	int	i;

	i = -1;
	write(STDOUT_FILENO, msg, strlen(msg));
	free_malloc(game);
	if (str != NULL)
		free(str);
	if (err == 1)
	{
		while (game->cub[++i])
			free(game->cub[i]);
		free(game->cub);
	}
	exit(1);
}

void	free_strings(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

int	close_win_free(t_game *game)
{
	free_cube(game);
	exit(0);
}

void	free_malloc(t_game *game)
{
	int	i;

	i = -1;
	free(game->player);
	while (++i < 4)
		free(game->wall[i]);
	free(game->wall);
	free(game->map);
	if (game->no)
		free(game->no);
	if (game->so)
		free(game->so);
	if (game->ea)
		free(game->ea);
	if (game->we)
		free(game->we);
	return ;
}

void	free_cube(t_game *game)
{
	int	i;

	i = -1;
	free_malloc(game);
	while (game->cub[++i])
		free(game->cub[i]);
	free(game->cub);
	mlx_destroy_image(game->mlx, game->texture.image);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	return ;
}
