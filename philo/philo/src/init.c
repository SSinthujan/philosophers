/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:05:23 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/05/25 04:12:00 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_mutex(t_program *prog)
{
	if (pthread_mutex_init(&prog->write_lock, NULL) != 0)
		return (write(2, "Failed to initialize mutex\n", 28), 1);
	if (pthread_mutex_init(&prog->dead_lock, NULL) != 0)
		return (write(2, "Failed to initialize mutex\n", 28), 1);
	if (pthread_mutex_init(&prog->meal_lock, NULL) != 0)
		return (write(2, "Failed to initialize mutex\n", 28), 1);
	if (pthread_mutex_init(&prog->everyoneate_lock, NULL) != 0)
		return (write(2, "Failed to initialize mutex\n", 28), 1);
	if (pthread_mutex_init(&prog->lastmeal_lock, NULL) != 0)
		return (write(2, "Failed to initialize mutex\n", 28), 1);
	return (0);
}

int	ft_join(t_philo *philo, t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			ft_exit(prog, philo, i);
			return (write(2, "Failed to join thread\n", 23), 1);
		}
		i++;
	}
	return (0);
}

int	ft_init(t_philo *philo, t_program *prog)
{
	int	i;

	i = 0;
	philo->prog->start_time = get_milliseconds();
	if (prog->num_of_philos == 1)
	{
		one_philo(philo);
		return (0);
	}
	while (i < prog->num_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &ft_routine, &philo[i]) != 0)
		{
			ft_exit(prog, philo, i);
			return (write(2, "Failed to create thread\n", 25), 1);
		}
		i++;
	}
	ft_monitoring(philo);
	if (ft_join(philo, prog) != 0)
		return (1);
	return (0);
}

int	ft_init_philo(t_philo *philo, t_program *prog)
{
	int	i;

	i = 0;
	prog->dead_flag = 0;
	prog->everyone_ate = 0;
	if (!philo)
		return (write(2, "Error philo initialization\n", 28), 1);
	while (i < prog->num_of_philos)
	{
		philo[i].id = i;
		philo[i].meal = 0;
		philo[i].prog = prog;
		philo[i].last_meal = get_milliseconds();
		philo[i].r_fork = &philo[(i + 1) % philo->prog->num_of_philos].l_fork;
		if (pthread_mutex_init(&philo[i].l_fork, NULL) != 0)
		{
			ft_exit(prog, philo, i);
			return (write(2, "Failed to initialize mutex\n", 28), 1);
		}
		i++;
	}
	if (ft_init(philo, prog) != 0)
		return (1);
	return (0);
}
