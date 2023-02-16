/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:41:57 by oidboufk          #+#    #+#             */
/*   Updated: 2023/02/16 12:14:23 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *philo)
{
	philo = (t_philo *)philo;
	return (NULL);
}

void	process(t_philo	philo)
{
	if (pthread_create(&philo.check, NULL, check_death, &philo))
		(printf("Can't Create thread.\n"), exit(0));
	else
		pthread_detach(philo.check);
	while (1)
	{
		sem_wait(philo.sem);
		printf("philosopher_%d has taken a fork.\n", philo.id);
		sem_wait(philo.sem);
		printf("philosopher_%d has taken a fork.\n", philo.id);
		printf("philosopher_%d is eating.\n", philo.id);
		usleep(philo.time_to_eat);
		philo.last_eat = timestamp(philo.start);
		sem_post(philo.sem);
		sem_post(philo.sem);
		printf("philosopher_%d is sleeping.\n", philo.id);
		usleep(philo.time_to_sleep);
	}
	exit(0);
}

void	init(t_philo *philo, char *av[], int ac)
{
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]) * 1000;
	philo->time_to_sleep = ft_atoi(av[4]) * 1000;
	philo->last_eat = 0;
	gettimeofday(&philo->start, NULL);
	if (ac == 6)
		philo->nb_to_eat = ft_atoi(av[5]);
}

int	main(int ac, char *av[])
{
	t_philo	philo;
	int		i;

	if (!handle_args(ac, av))
		return (printf("invalid args!\n"), 0);
	(sem_unlink("forks"), init(&philo, av, ac));
	philo.sem = sem_open("forks", O_CREAT | O_EXCL, 0666, ft_atoi(av[1]));
	i = 0;
	while (i++ < ft_atoi(av[1]))
	{
		philo.id = i;
		philo.pid = fork();
		if (philo.pid == 0)
			process(philo);
		usleep(150);
	}
	sem_close(philo.sem);
	sem_unlink("forks");
	i = 0;
	while (i++ < ft_atoi(av[1]))
		wait(NULL);
	return (0);
}
