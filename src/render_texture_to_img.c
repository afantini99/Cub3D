/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture_to_img.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:12:51 by luigi             #+#    #+#             */
/*   Updated: 2024/06/15 12:22:59 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../build/inc/cub3d.h"

static void	img_render(t_game *game, int *texture, char *path)
{
	int		x;
	int		y;
	t_image	img;

	img.image = mlx_xpm_file_to_image(game->mlx, path, &img.width, &img.height);
	if (!img.image)
	{
		write(STDOUT_FILENO, "Error:\nInvalid texture\n", 24);
		free_cube(game);
		exit(1);
	}
	img.addr = (int *)mlx_get_data_addr(img.image, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	y = -1;
	while (++y < img.height)
	{
		x = -1;
		while (++x < img.width)
			texture[img.width * y + x] = img.addr[img.width * y + x];
	}
	mlx_destroy_image(game->mlx, img.image);
	return ;
}

void	render_texture_to_img(t_game *game)
{
	img_render(game, game->wall[SO], game->so);
	img_render(game, game->wall[NO], game->no);
	img_render(game, game->wall[EA], game->ea);
	img_render(game, game->wall[WE], game->we);
	return ;
}
