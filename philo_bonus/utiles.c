/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:08:27 by oidboufk          #+#    #+#             */
/*   Updated: 2023/02/16 15:16:59 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	gettime(void)
{
	struct timeval	tv;
	long			end;

	gettimeofday(&tv, NULL);
	end = (tv.tv_sec * 1000000) + tv.tv_usec;
	return (end);
}

void	ft_usleep(long time)
{
	long	end;

	end = gettime() + time;
	while (gettime() < end)
		usleep(50);
}

double	timestamp(struct timeval start)
{
	double			timestamp;
	struct timeval	end;

	gettimeofday(&end, NULL);
	timestamp = (end.tv_sec - start.tv_sec) * 1000.0;
	timestamp += (end.tv_usec - start.tv_usec) / 1000.0;
	return (timestamp);
}
