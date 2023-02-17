/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:41:57 by oidboufk          #+#    #+#             */
/*   Updated: 2023/02/17 11:01:47 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	action(int id, t_philo *philo, char *str)
{
	sem_wait(philo->print);
	printf("%.0f %d %s\n", timestamp(philo->start), id, str);
	sem_post(philo->print);
	return (0);
}

void	*check_death(void *philo)
{
	double	last;

	while (1)
	{
		last = ((t_philo *)philo)->last_eat;
		if (timestamp(((t_philo *)philo)->start)
			- last >= ((t_philo *)philo)->time_to_die)
		{
			sem_wait(((t_philo *)philo)->print);
			printf("%.0f %d died\n",
				timestamp(((t_philo *)philo)->start), ((t_philo *)philo)->id);
			exit(0);
		}
		ft_usleep(1000);
	}
	return (NULL);
}

void	process(t_philo	philo)
{
	if (pthread_create(&philo.check, NULL, check_death, &philo))
		(printf("Can't Create thread.\n"), exit(0));
	pthread_detach(philo.check);
	while (1)
	{
		sem_wait(philo.sem);
		action(philo.id, &philo, "has taken a fork");
		sem_wait(philo.sem);
		action(philo.id, &philo, "has taken a fork");
		action(philo.id, &philo, "is eating");
		usleep(philo.time_to_eat);
		philo.last_eat = timestamp(philo.start);
		philo.eats++;
		sem_post(philo.sem);
		sem_post(philo.sem);
		action(philo.id, &philo, "is sleeping");
		usleep(philo.time_to_sleep);
		action(philo.id, &philo, "is thinking");
		if (philo.nb_to_eat != -1 && philo.eats == philo.nb_to_eat)
			exit(1);
	}
}

void	init(t_philo *philo, char *av[], int ac)
{
	philo->nb_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]) * 1000;
	philo->time_to_sleep = ft_atoi(av[4]) * 1000;
	philo->nb_to_eat = -1;
	philo->last_eat = 0;
	philo->eats = 0;
	gettimeofday(&philo->start, NULL);
	if (ac == 6)
		philo->nb_to_eat = ft_atoi(av[5]);
	philo->sem = sem_open("forks", O_CREAT | O_EXCL, 0666, philo->nb_philo);
	philo->print = sem_open("print", O_CREAT | O_EXCL, 0666, 1);
}

int	main(int ac, char *av[])
{
	t_philo		philo;
	int			i;
	static int	status = {1};

	if (!handle_args(ac, av))
		return (printf("invalid args!\n"), 0);
	(sem_unlink("forks"), sem_unlink("print"), init(&philo, av, ac));
	philo.pid = malloc(sizeof(int) * (philo.nb_philo + 1));
	i = -1;
	while (++i < philo.nb_philo)
	{
		philo.id = i + 1;
		philo.pid[i] = fork();
		((philo.pid[i] == 0) && (process(philo), 0));
		usleep(150);
	}
	i = -1;
	(sem_close(philo.sem), sem_unlink("forks"));
	(sem_close(philo.print), sem_unlink("print"));
	while (status && ++i < philo.nb_philo)
		wait(&status);
	i = -1;
	while (++i < philo.nb_philo)
		kill(philo.pid[i], SIGTERM);
	return (free(philo.pid), 0);
}
