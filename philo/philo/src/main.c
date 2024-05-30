/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 00:44:42 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/05/31 01:01:40 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine_solo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->prog->write_lock);
	printf("%zu %d has taken a fork\n", (get_milliseconds()
			- philo->prog->start_time), philo[0].id + 1);
	pthread_mutex_unlock(&philo->prog->write_lock);
	ft_usleep(philo->prog->time_to_die, philo->prog);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_lock(&philo->prog->write_lock);
	printf("%zu %d died\n", (get_milliseconds() - philo->prog->start_time),
		philo[0].id + 1);
	pthread_mutex_unlock(&philo->prog->write_lock);
	return (NULL);
}

void	one_philo(t_philo *philo)
{
	if (pthread_create(&philo[0].thread, NULL, ft_routine_solo, &philo[0]) != 0)
	{
		ft_exit(philo->prog, philo, 1);
		write(2, "Failed to create thread\n", 25);
		return ;
	}
	if (pthread_join(philo[0].thread, NULL) != 0)
	{
		ft_exit(philo->prog, philo, 1);
		write(2, "Failed to create join\n", 23);
		return ;
	}
}

void	ft_exit(t_program *prog, t_philo *philo, int i)
{
	int	k;

	k = 0;
	while (k < i)
	{
		pthread_join(philo[k].thread, NULL);
		k++;
	}
	k = 0;
	while (k < i)
	{
		pthread_mutex_destroy(&philo[k].l_fork);
		k++;
	}
	pthread_mutex_destroy(&prog->dead_lock);
	pthread_mutex_destroy(&prog->meal_lock);
	pthread_mutex_destroy(&prog->write_lock);
	pthread_mutex_destroy(&prog->everyoneate_lock);
	pthread_mutex_destroy(&prog->lastmeal_lock);
	free(philo);
	free(prog->philo);
}

int	main(int ac, char **av)
{
	static t_program	prog;
	static t_philo		*philo;

	if (ac != 5 && ac != 6)
		return (write(2, "Error number of arguments\n", 27), 1);
	if (is_num(av) != 0)
		return (1);
	if (ft_parse(&prog, av) != 0)
		return (1);
	philo = malloc(prog.num_of_philos * sizeof(t_philo));
	if (!philo)
		return (write(2, "Error malloc philos\n", 21), 1);
	if (ft_init_philo(philo, &prog) != 0)
		return (1);
	ft_exit(&prog, philo, prog.num_of_philos);
	return (0);
}
