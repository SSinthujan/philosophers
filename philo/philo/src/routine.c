/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 01:54:22 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/05/29 23:24:37 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lache_ca(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

void	ft_eating(t_philo *philo, t_program *prog)
{
	if (is_dead(philo->prog) == 1)
		return ;
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(&philo->l_fork);
	ft_write(philo, "has taken a fork");
	if (philo->id % 2 == 0)
		pthread_mutex_lock(&philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	ft_write(philo, "has taken a fork");
	ft_write(philo, "is eating");
	pthread_mutex_lock(&prog->lastmeal_lock);
	philo->last_meal = get_milliseconds();
	pthread_mutex_unlock(&prog->lastmeal_lock);
	ft_usleep(prog->time_to_eat, prog);
	lache_ca(philo);
}

void	ft_sleeping(t_philo *philo, t_program *prog)
{
	if (is_dead(philo->prog) == 1)
		return ;
	ft_write(philo, "is sleeping");
	ft_usleep(prog->time_to_sleep, prog);
	if (is_dead(philo->prog) == 1)
		return ;
	ft_write(philo, "is thinking");
	while ((prog->time_to_die - (get_milliseconds()
				- philo->last_meal)) > prog->time_to_eat && is_dead(prog) == 0)
		ft_usleep(1, prog);
}

void	*ft_routine(void *arg)
{
	t_philo		*philo;
	t_program	*prog;

	philo = (t_philo *)arg;
	prog = philo->prog;
	if (philo->id % 2 != 0)
		ft_usleep(prog->time_to_eat * 0.9, prog);
	while (is_dead(prog) == 0 && need_to_eat(philo, prog) == 0)
	{
		ft_eating(philo, prog);
		pthread_mutex_lock(&prog->meal_lock);
		philo->meal++;
		pthread_mutex_unlock(&prog->meal_lock);
		if (need_to_eat(philo, prog) == 1)
		{
			pthread_mutex_lock(&prog->everyoneate_lock);
			prog->everyone_ate++;
			pthread_mutex_unlock(&prog->everyoneate_lock);
			break ;
		}
		ft_sleeping(philo, prog);
	}
	return (NULL);
}
