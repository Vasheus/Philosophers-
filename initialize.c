/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 10:20:51 by yosabir           #+#    #+#             */
/*   Updated: 2024/12/27 15:09:18 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_died(t_philo *philo)
{
	int	status;

	if (philo == NULL)
		return (0);
	pthread_mutex_lock(philo->dead_lock);
	status = *philo->dead;
	pthread_mutex_unlock(philo->dead_lock);
	return (status);
}

void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo);
	while (!simulation_died(philo))
	{
		philo_eating(philo);
		if (simulation_died(philo))
			break ;
		philo_sleeping(philo);
		if (simulation_died(philo))
			break ;
		philo_thinking(philo);
	}
	return (NULL);
}

int	threads(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	monitoring;
	int			i;

	if (pthread_create(&monitoring, NULL, &monitor, data->philos) != 0)
		destroy(data, forks);
	i = 0;
	while (i < data->philos[0].philo_nmb)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine,
				&data->philos[i]) != 0)
			destroy(data, forks);
		i++;
	}
	i = 0;
	if (pthread_join(monitoring, NULL) != 0)
		destroy(data, forks);
	while (i < data->philos[0].philo_nmb)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			destroy(data, forks);
		i++;
	}
	return (0);
}
