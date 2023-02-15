/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:37:30 by oidboufk          #+#    #+#             */
/*   Updated: 2023/02/15 19:43:29 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		*philosophers;
	pthread_t		death_check;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	*mutex_ts;
	int				*nb_eat;
	long			nb_philo;
	double			*last_eat_ts;
	int				time_to_die;
	int				time_of_eat;
	int				nb_to_eat;
	int				time_of_sleep;
	int				id;
	struct timeval	start;
}	t_philo;
void		check_death(t_philo *philo);
double		timestamp(struct timeval start);
long		ft_atoi(char *str);
void		ft_usleep(long time);
int			action(int id, t_philo *test, struct timeval start, char *str);
void		complete_job(int id, t_philo *philo, struct timeval start);
pthread_t	*allocate(int len, pthread_mutex_t **forks,
				pthread_mutex_t **mutex_ts, double **last_eat_ts);
void		destroy_allocation(pthread_t **philo, pthread_mutex_t **forks,
				pthread_mutex_t **mutex_ts, double	**last_eat_ts);
int			check_nb_eat(t_philo *philo);
int			handle_args(int ac, char **av);
long		gettime(void);
#endif /* PHILO_H */