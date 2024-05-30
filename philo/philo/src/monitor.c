/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 03:39:59 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/05/25 04:27:35 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->prog->num_of_philos)
	{
		pthread_mutex_lock(&philo->prog->lastmeal_lock);
		if (philo->prog->time_to_die <= (get_milliseconds()
				- philo[i].last_meal))
		{
			pthread_mutex_lock(&philo->prog->dead_lock);
			philo->prog->dead_flag = 1;
			pthread_mutex_unlock(&philo->prog->dead_lock);
			pthread_mutex_lock(&philo->prog->write_lock);
			printf("%zu %d died\n", (get_milliseconds()
					- philo->prog->start_time), philo[i].id + 1);
			pthread_mutex_unlock(&philo->prog->write_lock);
			pthread_mutex_unlock(&philo->prog->lastmeal_lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->prog->lastmeal_lock);
		i++;
	}
	return (0);
}

int	ft_monitoring(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->prog->everyoneate_lock);
		if (philo->prog->everyone_ate == philo->prog->num_of_philos)
		{
			pthread_mutex_unlock(&philo->prog->everyoneate_lock);
			pthread_mutex_lock(&philo->prog->dead_lock);
			philo->prog->dead_flag = 1;
			pthread_mutex_unlock(&philo->prog->dead_lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->prog->everyoneate_lock);
		if (check_death(philo) != 0)
			return (1);
	}
}
