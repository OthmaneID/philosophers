/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:40:04 by oidboufk          #+#    #+#             */
/*   Updated: 2023/01/31 16:51:34 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <semaphore.h>

double	timestamp(struct timeval start)
{
	double			timestamp;
	struct timeval	end;

	gettimeofday(&end, NULL);
	timestamp = (end.tv_sec - start.tv_sec) * 1000.0;
	timestamp += (end.tv_usec - start.tv_usec) / 1000.0;
	return (timestamp);
}

int	action(int id, t_philo *philo, struct timeval start, char *str)
{
	(void)philo;
	printf("%.0f ms philosopher_%d %s\n", timestamp(start), id, str);
	return (0);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	int				id;
	struct timeval	start;

	philo = (t_philo *)arg;
	id = philo->id;
	start = philo->start;
	while (1)
		complete_job(id, philo, start);
	return (NULL);
}

void	init_philos(t_philo *philo, int ac, char *av[])
{
	int	i;

	i = -1;
	if (ac >= 5)
	{
		philo->time_to_die = ft_atoi(av[2]);
		philo->time_of_eat = ft_atoi(av[3]) * 1000;
		philo->time_of_sleep = ft_atoi(av[4]) * 1000;
		if (ac == 6)
			philo->nb_to_eat = ft_atoi(av[5]);
		else
			philo->nb_to_eat = -1;
		while (++i < philo->nb_philo)
		{
			philo->last_eat_ts[i] = 0.0;
			pthread_mutex_init(&philo->forks[i], NULL);
			pthread_mutex_init(&philo->mutex_ts[i], NULL);
			philo->nb_eat[i] = 0;
		}
	}
}

int	main(int ac, char *av[])
{
	t_philo		philo;
	int			i;

	i = -1;
	philo.nb_philo = (gettimeofday(&philo.start, NULL), ft_atoi(av[1]));
	philo.philosophers = allocate(philo.nb_philo, &philo.forks,
			&philo.mutex_ts, &philo.last_eat_ts);
	philo.nb_eat = malloc((philo.nb_philo + 1) * sizeof(int));
	init_philos(&philo, ac, av);
	while (++i < philo.nb_philo)
	{
		philo.id = i;
		if (pthread_create(&philo.philosophers[i], NULL, &routine, &philo))
			perror("ERROR : thread creation . \n");
		else if (pthread_detach(philo.philosophers[i]))
			perror("ERROR : thread detaching problem . \n");
		usleep(150);
	}
	check_death(&philo);
	destroy_allocation(&philo.philosophers, &philo.forks, &philo.mutex_ts,
		&philo.last_eat_ts);
	free(philo.nb_eat);
	return (0);
}
