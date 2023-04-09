/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:01:47 by dhendzel          #+#    #+#             */
/*   Updated: 2023/04/09 22:01:49 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	scream_return(void)
{
	system("pkill afplay &");
	system("afplay -v 0.5 ./music/scream.mp3 &");
	return (3);
}

int	scream_end(t_settings *settings)
{
	mlx_image_to_window(settings->mlx, settings->screamer, 0, 0);
	settings->max_distance = MAX_DISTANCE;
	return (4);
}

int	scream_start(void)
{
	system("afplay -v 0.5 ./music/background.mp3 &");
	return (2);
}

void	check_music(t_settings *settings)
{
	struct timeval	time;
	static int		scream = 1;
	static int		timer = 0;
	static int		scream_time = 0;

	gettimeofday(&time, NULL);
	if (!scream_time && scream == 1)
	{
		scream = scream_start();
		scream_time = time.tv_sec + TIMER;
		timer = TIMER;
	}
	if (scream_time - time.tv_sec < timer)
	{
		timer = scream_time - time.tv_sec;
		if (scream < 4)
			settings->max_distance -= MAX_DISTANCE / TIMER;
	}
	if ((scream_time - time.tv_sec) * 1000
		- time.tv_usec / 1000 < 1000 && scream < 3)
		scream = scream_return();
	if (timer == 0)
		scream = scream_end(settings);
	if (timer == -3)
		settings->screamer->enabled = false;
}
