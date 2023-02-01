/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:34:52 by oidboufk          #+#    #+#             */
/*   Updated: 2023/01/31 16:54:47 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_nb_eat(t_philo *philo)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < philo->nb_philo)
		if (philo->nb_eat[i] >= philo->nb_to_eat)
			count++;
	if (count == philo->nb_philo)
		return (1);
	else
		return (0);
}

void	destroy_allocation(pthread_t **philo, pthread_mutex_t **forks
	, pthread_mutex_t **mutex_ts, double	**last_eat_ts)
{
	if (*philo)
		free(*philo);
	if (*forks)
		free(*forks);
	if (*mutex_ts)
		free(*mutex_ts);
	if (*last_eat_ts)
		free(*last_eat_ts);
}
