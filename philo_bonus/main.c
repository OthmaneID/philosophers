/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:41:57 by oidboufk          #+#    #+#             */
/*   Updated: 2023/02/16 10:54:39 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo(sem_t *sem)
{
	sem_wait(sem);
	printf("proccessor is in\n");
	sleep(1);
	sem_post(sem);
	sem_close(sem);
	exit(0);
}

int	main(int ac, char *av[])
{
	int		pid;
	sem_t	*sem;

	(void)ac;
	(void)av;
	sem_unlink("forks");
	sem = sem_open("forks", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 1);
	pid = fork();
	if (pid == 0)
		philo(sem);
	pid = fork();
	if (pid == 0)
		philo(sem);
	sem_close(sem);
	sem_unlink("forks");
	wait(NULL);
	wait(NULL);
	return (0);
}
