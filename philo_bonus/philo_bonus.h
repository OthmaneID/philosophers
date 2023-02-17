/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:45:36 by oidboufk          #+#    #+#             */
/*   Updated: 2023/02/17 11:01:22 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <signal.h>
# include <stdatomic.h>

typedef struct s_philo
{
	sem_t			*sem;
	sem_t			*print;
	pthread_mutex_t	mut;
	pthread_t		check;
	int				id;
	int				*pid;
	int				time_to_sleep;
	int				time_to_die;
	int				time_to_eat;
	int				nb_to_eat;
	int				eats;
	int				nb_philo;
	double			last_eat;
	struct timeval	start;
}	t_philo;

long	ft_atoi(char *str);
int		handle_args(int ac, char **av);
void	ft_usleep(long time);
double	timestamp(struct timeval start);
long	gettime(void);
int		check_nb_eat(t_philo *philo, char *av[]);
#endif