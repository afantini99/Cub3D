/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_line_draw_setup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afantini <afantini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:10:03 by luigi             #+#    #+#             */
/*   Updated: 2024/06/28 15:02:57 by afantini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../build/inc/cub3d.h"

// floor() arrotonda verso il basso.
static void	get_wall(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x > 0 && ray->side == 0)
		ray->tex_num = EA;
	else if (ray->ray_dir_x < 0 && ray->side == 0)
		ray->tex_num = WE;
	else if (ray->ray_dir_y > 0 && ray->side == 1)
		ray->tex_num = NO;
	else
		ray->tex_num = SO;
	if (ray->side == 1)
		ray->wall_x = game->player->pos_x + ray->p_wall_dist
			* ray->ray_dir_x;
	else
		ray->wall_x = game->player->pos_y + ray->p_wall_dist
			* ray->ray_dir_y;
	ray->wall_x -= floor(ray->wall_x);
	return ;
}

// color >> 1: R, G, B --> R/2, G/2, B/2.
// & 8355711 (binario, in esa: 0x7F7F7F, 127, 127, 127): assicura che ogni 
// componente RGB del colore non superi mai il valore 127 (cioè 0x7F). 
// Altri valori: 0x3F3F3F (63, 63, 63), ecc.
static void	draw_wall(t_game *game, t_ray *ray, int x)
{
	int		y;
	int		color;
	double	step;

	step = 1.0 * TEX_SIZE / ray->line_height;
	ray->tex_pos = \
		(ray->draw_start - SCREEN_H / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (TEX_SIZE - 1);
		ray->tex_pos += step;
		color = game->wall[ray->tex_num][TEX_SIZE * ray->tex_y + ray->tex_x];
		if (ray->side == 0)
			color = control_brightness(color, 125);
		game->texture.addr[SCREEN_W * y + x] = color;
		y++;
	}
	return ;
}

// x, colonna corrente dello schermo; y, posizione verticale nello schermo
static void	draw_color(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = -1;
	while (++y < SCREEN_H)
	{
		if (y < ray->draw_start)
			game->texture.addr[SCREEN_W * y + x] = game->ceiling;
		else if (y > ray->draw_end)
			game->texture.addr[SCREEN_W * y + x] = game->floor;
	}
	return ;
}

// l'idea non e' quella di disegnare soffitto e pavimento e poi
// sovrappore le texture dei muri, ma di riempire lo spazio
// rimanente dello schermo dopo la renderizzazione delle texture.
void	pixel_line_draw_setup(t_game *game, t_ray *ray, int x)
{
	ray->line_height = (int)(SCREEN_H / ray->p_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_H / 2;
	if (ray->draw_end >= SCREEN_H)
		ray->draw_end = SCREEN_H - 1;
	get_wall(game, ray);
	ray->tex_x = (int)(ray->wall_x * (double)TEX_SIZE);
	if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->tex_x = TEX_SIZE - ray->tex_x - 1;
	if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->tex_x = TEX_SIZE - ray->tex_x - 1;
	draw_wall(game, ray, x);
	draw_color(game, ray, x);
	return ;
}
