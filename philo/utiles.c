/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:03:21 by oidboufk          #+#    #+#             */
/*   Updated: 2023/02/15 20:54:20 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	long	res;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = 1 - 2 * (str[i++] == '-');
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (res * sign);
}

void	check_death(t_philo	*philo)
{
	int	i;

	i = philo->nb_philo;
	while (i == philo->nb_philo)
	{
		i = -1;
		while (++i < philo->nb_philo)
		{
			pthread_mutex_lock(&philo->mutex_ts[i]);
			if (timestamp(philo->start) - philo->last_eat_ts[i]
				>= philo->time_to_die)
			{
				pthread_mutex_lock(&philo->print);
				printf("%.0f %d died\n", timestamp(philo->start), i + 1);
				return ;
			}
			pthread_mutex_unlock(&philo->mutex_ts[i]);
			ft_usleep(5000 / philo->nb_philo);
			if (philo->nb_to_eat != -1)
				if (check_nb_eat(philo))
					return ;
		}
	}
}

void	complete_job(int id, t_philo *philo, struct timeval start)
{
	pthread_mutex_lock(&philo->forks[id]);
	action(id + 1, philo, start, "has taken a fork");
	pthread_mutex_lock(&philo->forks[(id + 1) % philo->nb_philo]);
	action(id + 1, philo, start, "has taken a fork");
	action(id + 1, philo, start, "is eating");
	ft_usleep(philo->time_of_eat);
	pthread_mutex_lock(&philo->mutex_ts[id]);
	philo->last_eat_ts[id] = timestamp(start);
	philo->nb_eat[id]++;
	pthread_mutex_unlock(&philo->mutex_ts[id]);
	pthread_mutex_unlock(&philo->forks[id]);
	pthread_mutex_unlock(&philo->forks[(id + 1) % philo->nb_philo]);
	action(id + 1, philo, start, "is sleeping");
	ft_usleep(philo->time_of_sleep);
	action(id + 1, philo, start, "is thinking");
}

void	ft_usleep(long time)
{
	long	end;

	end = gettime() + time;
	while (gettime() < end)
		usleep(50);
}
// void	ft_usleep(long time)
// {
// 	struct timeval	start;
// 	double			amount;
// 	double			sleept;

// 	amount = time / 1000;
// 	while (time >= amount)
// 	{
// 		gettimeofday(&start, NULL);
// 		usleep(amount);
// 		sleept = timestamp(start) * 1000;
// 		time -= sleept;
// 	}
// }

//return a philo pointer
pthread_t	*allocate(int len, pthread_mutex_t **forks
		, pthread_mutex_t **mutex_ts, double **last_eat_ts)
{
	pthread_t	*philo;

	(*forks) = malloc(((size_t)len + 1) * sizeof(pthread_mutex_t));
	(*mutex_ts) = malloc(((size_t)len + 1) * sizeof(pthread_mutex_t));
	(*last_eat_ts) = malloc(((size_t)len + 1) * sizeof(double));
	philo = malloc(((size_t)len + 1) * sizeof(pthread_t));
	return (philo);
}
