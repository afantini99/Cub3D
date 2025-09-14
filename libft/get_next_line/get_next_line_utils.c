/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:03:44 by larmogid          #+#    #+#             */
/*   Updated: 2024/06/14 07:53:27 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_generate_line(char *str_to_subd)
{
	char	*str;
	int		i;

	i = 0;
	if (!str_to_subd[i])
		return (NULL);
	while (str_to_subd[i] && str_to_subd[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (str_to_subd[i] && str_to_subd[i] != '\n')
	{
		str[i] = str_to_subd[i];
		i++;
	}
	if (str_to_subd[i] == '\n')
	{
		str[i] = str_to_subd[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_get_next(char *str_to_subd)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (str_to_subd[i] && str_to_subd[i] != '\n')
		i++;
	if (!str_to_subd[i])
	{
		free(str_to_subd);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(str_to_subd) - i + 1));
	if (!str)
	{
		free(str_to_subd);
		return (NULL);
	}
	i++;
	j = 0;
	while (str_to_subd[i])
		str[j++] = str_to_subd[i++];
	str[j] = '\0';
	free(str_to_subd);
	return (str);
}
