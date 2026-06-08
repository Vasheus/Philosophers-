/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:39:43 by yosabir           #+#    #+#             */
/*   Updated: 2024/12/27 15:41:28 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_t		thread;
	int				id;
	int				eating;
	int				eat_times;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				philo_nmb;
	int				total_meals;
	int				*dead;
	int				end_it;
}					t_philo;

typedef struct s_data
{
	int				dead_sim;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_data;

int					ft_strlen(char *str);
void				destroy(t_data *data, pthread_mutex_t *forks);
int					input_check(char ac, char **av);
int					philosopher_dead(t_philo *philo, size_t time_to_die);
void				start_sim(char *str, t_philo *philo, int id);
int					ft_atoi(char *str);
void				init(t_data *data, t_philo *philos,
						pthread_mutex_t *forks, char **av);
size_t				get_time(void);
void				init_philos(t_philo *philos, t_data *data,
						pthread_mutex_t *forks, char **av);
void				init_input(t_philo *philo, char **av);
int					check_full(t_philo *philos);
int					threads(t_data *data, pthread_mutex_t *forks);
void				*monitor(void *pointer);
void				*routine(void *pointer);
void				philo_eating(t_philo *philo);
void				philo_sleeping(t_philo *philo);
void				philo_thinking(t_philo *philo);
int					simulation_died(t_philo *philo);
int					check_death(t_philo *philos);
int					ft_usleep(size_t microseconds, t_philo *philo);

#endif
