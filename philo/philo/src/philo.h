/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssitchsa <ssitchsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 00:44:45 by ssitchsa          #+#    #+#             */
/*   Updated: 2024/05/25 04:12:12 by ssitchsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct program	t_program;

typedef struct philo
{
	pthread_t			thread;
	int					id;
	int					meal;
	size_t				last_meal;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		l_fork;
	t_program			*prog;
}						t_philo;

typedef struct program
{
	int					dead_flag;
	int					num_of_philos;
	int					everyone_ate;
	int					num_times_to_eat;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				start_time;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		everyoneate_lock;
	pthread_mutex_t		lastmeal_lock;
	t_philo				*philo;
}						t_program;

int						is_num(char **argv);
long					ft_atol(char *str);
int						ft_parse(t_program *prog, char **av);
int						ft_init_mutex(t_program *prog);
int						ft_init(t_philo *philo, t_program *prog);
int						ft_init_philo(t_philo *philo, t_program *prog);
int						is_dead(t_program *prog);
int						need_to_eat(t_philo *philo, t_program *prog);
int						ft_usleep(size_t milliseconds, t_program *prog);
size_t					get_milliseconds(void);
int						ft_monitoring(t_philo *philo);
void					one_philo(t_philo *philo);
void					*ft_routine_solo(void *arg);
void					*ft_routine(void *arg);
void					ft_sleeping(t_philo *philo, t_program *prog);
void					ft_thinking(t_philo *philo, t_program *prog);
int						ft_write(t_philo *philo, char *str);
void					ft_exit(t_program *prog, t_philo *philo, int i);

#endif