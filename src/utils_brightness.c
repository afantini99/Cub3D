/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_brightness.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luigi <luigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 09:01:46 by luigi             #+#    #+#             */
/*   Updated: 2024/06/19 09:08:06 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../build/inc/cub3d.h"

// Funzione ausiliaria per assicurare che un valore sia nel range specificato
static int	check_range(int value, int min, int max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	else
		return (value);
}

// Ricompone il colore modificato; factor --> fattore di riduzione
unsigned int	control_brightness(unsigned int color, int factor)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * factor / 255;
	g = ((color >> 8) & 0xFF) * factor / 255;
	b = (color & 0xFF) * factor / 255;
	r = check_range(r, 0, 255);
	g = check_range(g, 0, 255);
	b = check_range(b, 0, 255);
	return ((r << 16) | (g << 8) | b);
}
