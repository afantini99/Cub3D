/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_keys_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:37:02 by luigi             #+#    #+#             */
/*   Updated: 2024/06/19 00:32:34 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../build/inc/cub3d.h"

// down --> premuto
int	keydown_hook(int keycode, t_game *game)
{
	if (keycode == KEY_A)
		game->key_a = 1;
	else if (keycode == KEY_S)
		game->key_s = 1;
	else if (keycode == KEY_D)
		game->key_d = 1;
	else if (keycode == KEY_W)
		game->key_w = 1;
	else if (keycode == KEY_ARROW_LEFT)
		game->key_left = 1;
	else if (keycode == KEY_ARROW_RIGHT)
		game->key_right = 1;
	return (0);
}

// up --> rilasciato
int	keyup_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_win_free(game);
	else if (keycode == KEY_A)
		game->key_a = 0;
	else if (keycode == KEY_S)
		game->key_s = 0;
	else if (keycode == KEY_D)
		game->key_d = 0;
	else if (keycode == KEY_W)
		game->key_w = 0;
	else if (keycode == KEY_ARROW_LEFT)
		game->key_left = 0;
	else if (keycode == KEY_ARROW_RIGHT)
		game->key_right = 0;
	return (0);
}
