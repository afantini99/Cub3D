/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afantini <afantini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:13:26 by luigi             #+#    #+#             */
/*   Updated: 2024/06/28 16:24:06 by afantini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../build/inc/cub3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	free_array(char **s)
{
	int		i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	return ;
}

char	*check_strjoin(t_game *game, char *tmp, char *line, int fd)
{
	char	*new;

	new = ft_strjoin(tmp, line);
	free_strings(tmp, line);
	if (!new)
	{
		close(fd);
		write_error_n_exit(1, "Error:\nFailed to join strings\n", NULL, game);
	}
	return (new);
}

int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	skip_spaces(char *line)
{
	int		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] && !ft_isspace(line[i]))
		return (0);
	return (1);
}
