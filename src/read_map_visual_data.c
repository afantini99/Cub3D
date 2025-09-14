/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_visual_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afantini <afantini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:40:05 by luigi             #+#    #+#             */
/*   Updated: 2024/06/28 16:23:40 by afantini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../build/inc/cub3d.h"

char	*get_info(t_game *game, char *line)
{
	char	**temp;
	char	*file;
	int		fd;

	temp = ft_split(line, ' ');
	if (!temp)
		write_error_n_exit(0, "Error:\nInformation Error\n", NULL, game);
	if (temp[2])
	{
		free_array(temp);
		write_error_n_exit(1, "Error:\nFormat Error\n", NULL, game);
	}
	file = ft_strdup(temp[1]);
	free_array(temp);
	fd = open(file, O_DIRECTORY);
	if (fd < 0)
		fd = open(file, O_RDONLY);
	else
		write_error_n_exit(1, "Error:\nFailed to open the map image\n",
			file, game);
	if (fd < 0)
		write_error_n_exit(1, "Error:\nFailed to open the map image\n",
			file, game);
	game->info++;
	return (file);
}

void	read_map_visual_data(t_game *game, char **line, int *i)
{
	while (line[++(*i)] && game->info < 6)
	{
		if (!ft_strncmp(line[*i], "WE ", 3) && game->we == NULL)
			game->we = get_info(game, line[*i]);
		else if (!ft_strncmp(line[*i], "NO ", 3) && game->no == NULL)
			game->no = get_info(game, line[*i]);
		else if (!ft_strncmp(line[*i], "SO ", 3) && game->so == NULL)
			game->so = get_info(game, line[*i]);
		else if (!ft_strncmp(line[*i], "EA ", 3) && game->ea == NULL)
			game->ea = get_info(game, line[*i]);
		else if (!ft_strncmp(line[*i], "F ", 2) && game->floor == -1)
			map_background(game, line[*i], FLOOR);
		else if (!ft_strncmp(line[*i], "C ", 2) && game->ceiling == -1)
			map_background(game, line[*i], CEILING);
		else
			write_error_n_exit(1, "Error:\nWrong information\n", NULL, game);
	}
	return ;
}
