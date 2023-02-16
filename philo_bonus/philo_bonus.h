/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:45:36 by oidboufk          #+#    #+#             */
/*   Updated: 2023/02/16 11:30:16 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo
{
	sem_t			*sem;
	pthread_mutex_t	mut;
	pthread_t		check;
	int				id;
	int				pid;
	int				time_to_sleep;
	int				time_to_die;
	int				time_to_eat;
}	t_philo;

long	ft_atoi(char *str);
int		handle_args(int ac, char **av);
#endif