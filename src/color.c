/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 22:28:08 by dhendzel          #+#    #+#             */
/*   Updated: 2023/04/10 02:48:58 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	splitted_len(char **splitted)
{
	int	i;

	if (!splitted)
		return (0);
	i = 0;
	while (splitted[i])
		i++;
	return (i);
}

unsigned long	create_rgba(char **splitted, bool *check)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;

	r = ft_atoi(splitted[0]);
	g = ft_atoi(splitted[1]);
	b = ft_atoi(splitted[2]);
	if (r > 255 || g > 255 || b > 255)
	{
		r = 0;
		g = 0;
		b = 0;
		*check = false;
	}	
	a = 255;
	return (((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8)
		+ (a & 0xff));
}

bool	create_color(t_settings *res, char key)
{
	char	**splitted;
	bool	check;

	splitted = NULL;
	check = true;
	if (key == 'C')
		splitted = ft_split(dict_get(res->dict, "C\0", "hui"), ",");
	else if (key == 'F')
		splitted = ft_split(dict_get(res->dict, "F\0", "hui"), ",");
	if (splitted_len(splitted) != 3)
	{
		ft_split_clear(splitted);
		return (false);
	}
	if (key == 'F')
		res->floor_color = create_rgba(splitted, &check);
	else if (key == 'C')
		res->ceiling_color = create_rgba(splitted, &check);
	ft_split_clear(splitted);
	if (!check)
		return (false);
	return (true);
}

int	get_color(uint32_t color, float darkness)
{
	int	r;
	int	g;
	int	b;
	int	t;
	int	res_color;

	r = color >> 24 & 255;
	g = color >> 16 & 255;
	b = color >> 8 & 255;
	t = color & 255;
	res_color = (int)(r * darkness) << 24
		| (int)(g * darkness) << 16 | (int)(b * darkness) << 8 | t;
	return (res_color);
}
