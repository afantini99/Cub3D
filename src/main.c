/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afantini <afantini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:15:54 by luigi             #+#    #+#             */
/*   Updated: 2024/06/28 16:21:55 by afantini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../build/inc/cub3d.h"

static void	generate_map(t_game *game)
{
	int		x;
	t_ray	ray;

	x = -1;
	while (++x < SCREEN_W)
	{
		raycasting_setup(game, &ray, x);
		pixel_line_draw_setup(game, &ray, x);
	}
	return ;
}

static int	game_main_loop(t_game *game)
{
	generate_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->texture.image, 0, 0);
	player_actions(game);
	return (0);
}

// game_main_loop --> map_generate --> ray_init
// mlx_loop --> loop degli eventi
// keydown --> premuto; keyup --> rilasciato
static void	map_controls(t_game *game)
{
	if (game->info != 6)
		write_error_n_exit(1, "Error:\nMap info are not enough\n", NULL, game);
	if (check_map_wall(game) == FAILURE)
		write_error_n_exit(1, "Error:\nThe map is open or invalid\n",
			NULL, game);
	check_map_contents(game);
	if (game->pl_pos_cnt != 1)
		write_error_n_exit(1, "Error:\nInvalid Map. Player number error\n",
			NULL, game);
	return ;
}

int	main(int argc, char **argv)
{
	t_game		game;
	const char	*err_msg = NULL;

	if (argc != 2)
	{
		err_msg = "Error:\nMap file missing o||r Bad arguments\n";
		write(STDOUT_FILENO, err_msg, strlen(err_msg));
		exit(1);
	}
	initialize_data(&game);
	read_map_cells(&game, argv[1]);
	map_controls(&game);
	initialize_game_env(&game);
	render_texture_to_img(&game);
	mlx_hook(game.win, 2, 1L << 0, keydown_hook, &game);
	mlx_hook(game.win, 17, 0, close_win_free, &game);
	mlx_key_hook(game.win, keyup_hook, &game);
	mlx_loop_hook(game.mlx, game_main_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
