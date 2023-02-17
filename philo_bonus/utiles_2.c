/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:22:55 by oidboufk          #+#    #+#             */
/*   Updated: 2023/02/16 20:37:59 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_nb_eat(t_philo *philo, char *av[])
{
	int	nb;

	nb = ft_atoi(av[5]);
	if (philo->eats >= nb)
		return (1);
	else
		return (0);
}
