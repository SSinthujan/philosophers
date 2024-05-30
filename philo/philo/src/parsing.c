/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 01:39:59 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/05/25 01:03:25 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_num(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (write(2, "Error argument\n", 16), 1);
			j++;
		}
		i++;
	}
	return (0);
}

long	ft_atol(char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (!str || !(*str))
		return (0);
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + (str[i] - '0');
		if ((result * sign) > INT_MAX || (result * sign) < INT_MIN)
			return (INT_MAX + 1L);
		i++;
	}
	return (result * sign);
}

int	ft_parse(t_program *prog, char **av)
{
	if (ft_atol(av[1]) > 200 || ft_atol(av[1]) <= 0)
		return (write(2, "Error value number of philosophers\n", 36), 1);
	prog->num_of_philos = ft_atol(av[1]);
	if (ft_atol(av[2]) <= 0 || ft_atol(av[2]) > INT_MAX)
		return (write(2, "Error value time to die\n", 25), 1);
	prog->time_to_die = ft_atol(av[2]);
	if (ft_atol(av[3]) <= 0 || ft_atol(av[3]) > INT_MAX)
		return (write(2, "Error value time to eat\n", 25), 1);
	prog->time_to_eat = ft_atol(av[3]);
	if (ft_atol(av[4]) <= 0 || ft_atol(av[4]) > INT_MAX)
		return (write(2, "Error value time to sleep\n", 27), 1);
	prog->time_to_sleep = ft_atol(av[4]);
	if (av[5])
	{
		if (ft_atol(av[5]) <= 0 || ft_atol(av[5]) > INT_MAX)
			return (write(2, "Error value number to eat\n", 27), 1);
		prog->num_times_to_eat = ft_atol(av[5]);
	}
	else
		prog->num_times_to_eat = -1;
	if (ft_init_mutex(prog) != 0)
		return (1);
	return (0);
}
