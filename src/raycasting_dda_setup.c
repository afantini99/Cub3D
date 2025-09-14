/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_dda_setup.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:56:19 by luigi             #+#    #+#             */
/*   Updated: 2024/06/19 10:24:06 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../build/inc/cub3d.h"

// 1° if () --> aggiorna le distanze: side = side + delta
// 2° if (): ray->hit = 1 --> la cella contiene un muro (collisione)
void	run_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->d_dist_x;
			ray->x_cell += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->d_dist_y;
			ray->y_cell += ray->step_y;
			ray->side = 1;
		}
		if (game->map[ray->y_cell][ray->x_cell] == '1')
			ray->hit = 1;
	}
	return ;
}

void	initialize_dda(t_game *game, t_ray *ray)
{
	t_player	*g_player;

	g_player = game->player;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (g_player->pos_x - ray->x_cell) * ray->d_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->x_cell + 1.0 - g_player->pos_x)
			* ray->d_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (g_player->pos_y - ray->y_cell) * ray->d_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->y_cell + 1.0 - g_player->pos_y)
			* ray->d_dist_y;
	}
}
