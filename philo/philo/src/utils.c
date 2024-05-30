/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:30:51 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/05/29 23:23:39 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_program *prog)
{
	int	i;

	pthread_mutex_lock(&prog->dead_lock);
	i = prog->dead_flag;
	pthread_mutex_unlock(&prog->dead_lock);
	return (i);
}

int	need_to_eat(t_philo *philo, t_program *prog)
{
	int	i;

	pthread_mutex_lock(&prog->meal_lock);
	i = philo->meal;
	pthread_mutex_unlock(&prog->meal_lock);
	if (i == prog->num_times_to_eat)
		return (1);
	return (0);
}

size_t	get_milliseconds(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Error gettimeofday\n", 20);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(size_t milliseconds, t_program *prog)
{
	size_t	start_time;

	start_time = get_milliseconds();
	while (((get_milliseconds() - start_time) < milliseconds)
		&& prog->everyone_ate <= prog->num_of_philos && is_dead(prog) == 0)
		usleep(500);
	return (0);
}

int	ft_write(t_philo *philo, char *str)
{
	if (is_dead(philo->prog) == 0)
	{
		pthread_mutex_lock(&philo->prog->write_lock);
		printf("%zu %d %s\n", (get_milliseconds() - philo->prog->start_time),
			philo->id + 1, str);
		pthread_mutex_unlock(&philo->prog->write_lock);
		return (0);
	}
	return (1);
}
