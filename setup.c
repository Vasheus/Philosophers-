/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:29:40 by yosabir           #+#    #+#             */
/*   Updated: 2024/12/27 13:30:09 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_input(t_philo *philo, char **av)
{
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->philo_nmb = ft_atoi(av[1]);
	if (av[5])
		philo->total_meals = ft_atoi(av[5]);
	else
		philo->total_meals = -1;
}

void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks,
		char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].eat_times = 0;
		init_input(&philos[i], av);
		philos[i].start_time = get_time();
		philos[i].last_meal = get_time();
		philos[i].write_lock = &data->write_lock;
		philos[i].dead_lock = &data->dead_lock;
		philos[i].meal_lock = &data->meal_lock;
		philos[i].dead = &data->dead_sim;
		philos[i].l_fork = &forks[i];
		philos[i].end_it = data->dead_sim;
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].philo_nmb - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init(t_data *data, t_philo *philos, pthread_mutex_t *forks, char **av)
{
	int	i;

	i = 0;
	data->dead_sim = 0;
	data->philos = philos;
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		destroy(data, forks);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		destroy(data, forks);
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
		destroy(data, forks);
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
