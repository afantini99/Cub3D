/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:13:17 by luigi             #+#    #+#             */
/*   Updated: 2024/06/19 10:34:15 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../build/inc/cub3d.h"

static void	initialize_ray_direction(t_game *game, t_ray *ray, int x)
{
	t_player	*g_player;
	double		camera_x;

	g_player = game->player;
	camera_x = 2 * x / (double)SCREEN_W - 1;
	ray->ray_dir_x = g_player->dir_x + g_player->plane_x * camera_x;
	ray->ray_dir_y = g_player->dir_y + g_player->plane_y * camera_x;
	return ;
}

static void	calculate_distance_steps(t_game *game, t_ray *ray)
{
	t_player	*g_player;

	g_player = game->player;
	ray->x_cell = (int)g_player->pos_x;
	ray->y_cell = (int)g_player->pos_y;
	ray->d_dist_x = sqrt(1 + (ray->ray_dir_y * ray->ray_dir_y)
			/ (ray->ray_dir_x * ray->ray_dir_x));
	ray->d_dist_y = sqrt(1 + (ray->ray_dir_x * ray->ray_dir_x)
			/ (ray->ray_dir_y * ray->ray_dir_y));
	return ;
}

static void	calculate_perpendicular_distance(t_game *game, t_ray *ray)
{
	t_player	*g_pl;

	g_pl = game->player;
	if (ray->side == 0)
		ray->p_wall_dist = (ray->x_cell - g_pl->pos_x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else
		ray->p_wall_dist = (ray->y_cell - g_pl->pos_y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
	return ;
}

void	raycasting_setup(t_game *game, t_ray *ray, int x)
{
	initialize_ray_direction(game, ray, x);
	calculate_distance_steps(game, ray);
	ray->hit = 0;
	initialize_dda(game, ray);
	run_dda(game, ray);
	calculate_perpendicular_distance(game, ray);
	return ;
}
