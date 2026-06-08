/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:27:03 by yosabir           #+#    #+#             */
/*   Updated: 2024/12/27 15:16:16 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo)
{
	ft_usleep(philo->time_to_die, philo);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	start_sim("has taken a fork", philo, philo->id);
	if (philo->philo_nmb == 1)
	{
		one_philo(philo);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	start_sim("has taken a fork", philo, philo->id);
	philo->eating = 1;
	start_sim("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->eat_times++;
	pthread_mutex_unlock(philo->meal_lock);
	if (ft_usleep(philo->time_to_eat, philo))
	{
		philo->eating = 0;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleeping(t_philo *philo)
{
	if (ft_usleep(philo->time_to_sleep, philo))
		return ;
	start_sim("is sleeping", philo, philo->id);
}

void	philo_thinking(t_philo *philo)
{
	start_sim("is thinking", philo, philo->id);
}
