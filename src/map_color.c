/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afantini <afantini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:12:15 by luigi             #+#    #+#             */
/*   Updated: 2024/06/28 16:22:17 by afantini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../build/inc/cub3d.h"

int	is_color(char *str, int flag)
{
	int	i;

	i = -1;
	if (flag == 0)
	{
		while (str[++i])
		{
			if (!ft_isdigit(str[i]))
				return (1);
		}
	}
	else
	{
		while (*str++)
		{
			if (*str == ',')
				i++;
		}
		if (i == 1)
			return (1);
	}
	return (0);
}

int	get_rgb_color(char *line, int *rgb, int *i)
{
	char	**temp;
	int		color;
	int		j;

	temp = ft_split(line, ',');
	j = -1;
	while (temp[++j])
	{
		if (is_color(temp[j], 0))
		{
			free_array(temp);
			return (1);
		}
		color = ft_atoi(temp[j]);
		if (color < 0 || color > 255)
		{
			free_array(temp);
			return (1);
		}
		rgb[*i] = color;
		(*i)++;
	}
	free_array(temp);
	return (0);
}

void	map_coloring(t_game *game, int *rgb, int info)
{
	if (rgb[0] < 0 || rgb[1] < 0 || rgb[2] < 0)
		write_error_n_exit(1, "Error:\nColor info not valid\n", NULL, game);
	if (info == FLOOR)
		game->floor = (0 << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	else
		game->ceiling = (0 << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	game->info++;
	return ;
}

void	map_background(t_game *game, char *line, int info)
{
	char	**color;
	int		i;
	int		rgb[3];
	int		count;

	color = NULL;
	rgb[0] = -1;
	rgb[1] = -1;
	rgb[2] = -1;
	if (is_color(line, 1))
		color = ft_split(line, ' ');
	else
		write_error_n_exit(1, "Error:\nColor info not valid\n", NULL, game);
	i = 0;
	count = 0;
	while (color[++i])
	{
		if (get_rgb_color(color[i], rgb, &count))
		{
			free_array(color);
			write_error_n_exit(1, "Error:\nColor info not valid\n", NULL, game);
		}
	}
	free_array(color);
	map_coloring(game, rgb, info);
}
