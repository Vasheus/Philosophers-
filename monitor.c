/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 09:57:41 by yosabir           #+#    #+#             */
/*   Updated: 2024/12/27 15:06:13 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_sim(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start_time;
	if (!simulation_died(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_death(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].philo_nmb)
	{
		if (philosopher_dead(&philos[i], philos[i].time_to_die))
		{
			start_sim("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_full(t_philo *philos)
{
	int	i;
	int	ready;

	i = 0;
	ready = 0;
	if (philos[0].total_meals == -1)
		return (0);
	while (i < philos[0].philo_nmb)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].eat_times >= philos[i].total_meals)
			ready++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (ready == philos[0].philo_nmb)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (check_death(philos) == 1 || check_full(philos) == 1)
			break ;
	return (pointer);
}
