/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_cells.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afantini <afantini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:12:44 by luigi             #+#    #+#             */
/*   Updated: 2024/06/28 16:22:47 by afantini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../build/inc/cub3d.h"

static void	check_map_size(t_game *game)
{
	int	i;
	int	tmp;

	i = -1;
	while (game->map[++i])
	{
		tmp = game->x;
		if (tmp < ft_strlen(game->map[i]))
			game->x = ft_strlen(game->map[i]);
	}
	if (game->y == 0 || game->x == 0)
		write_error_n_exit(1, "Error: Invalid map (empty)\n", NULL, game);
	return ;
}

static void	allocate_map(t_game *game, char **line, int *i)
{
	int		j;

	j = 0;
	game->map = (char **)malloc(sizeof(char *) * (game->size + 2));
	while (line[(*i)])
	{
		game->map[j++] = line[(*i)++];
		game->y++;
	}
	game->map[j] = NULL;
	return ;
}

static void	check_format_file(t_game *game, char *filename, int fd)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || !ft_strnstr(&filename[len - 4], ".cub", 4))
	{
		close(fd);
		write_error_n_exit(0, "Error: Map file extension is not .cub\n",
			NULL, game);
	}
	return ;
}

char	*read_map_lines(t_game *game, int fd)
{
	char	*line;
	char	*tmp;

	tmp = ft_strdup("");
	if (!tmp)
	{
		close(fd);
		write_error_n_exit(1, "Failed to allocate initial tmp string.\n",
			NULL, game);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		tmp = check_strjoin(game, tmp, line, fd);
		game->size++;
	}
	game->size -= 9;
	return (tmp);
}

void	read_map_cells(t_game *game, char *filename)
{
	int	fd;
	int	i;

	fd = open(filename, O_DIRECTORY);
	if (fd < 0)
		fd = open(filename, O_RDONLY);
	else
		write_error_n_exit(0, "Error:\nMap should be a file\n", NULL, game);
	if (fd <= 0)
		write_error_n_exit(0, "Error:\nFailed to open the map\n", NULL, game);
	check_format_file(game, filename, fd);
	i = -1;
	initialize_map(game, fd);
	close(fd);
	if (game->size == 0)
		write_error_n_exit(1, "Error:\nInvalid map (empty)\n", NULL, game);
	read_map_visual_data(game, game->cub, &i);
	allocate_map(game, game->cub, &i);
	check_map_size(game);
	return ;
}
