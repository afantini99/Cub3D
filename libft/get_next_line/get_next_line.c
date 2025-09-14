/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:03:18 by larmogid          #+#    #+#             */
/*   Updated: 2024/06/09 17:22:35 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_n_store(int fd, char *str_to_subd)
{
	char	*buff;
	int		bytes_read;
	char	*tmp;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(str_to_subd, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buff), NULL);
		buff[bytes_read] = '\0';
		tmp = ft_strjoin(str_to_subd, buff);
		if (!tmp)
			return (free(buff), free(str_to_subd), NULL);
		free(str_to_subd);
		str_to_subd = tmp;
	}
	return (free(buff), str_to_subd);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str_to_subd;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str_to_subd = ft_read_n_store(fd, str_to_subd);
	if (!str_to_subd)
		return (NULL);
	line = ft_generate_line(str_to_subd);
	str_to_subd = ft_get_next(str_to_subd);
	return (line);
}
