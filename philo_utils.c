/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:11:02 by yosabir           #+#    #+#             */
/*   Updated: 2024/12/27 14:55:05 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		sign;
	long	res;
	long	res1;

	res = 0;
	sign = 1;
	res1 = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = *str++ - '0' + (res * 10);
		if (res < res1 && sign == 1)
			return (-1);
		if (res < res1 && sign == -1)
			return (0);
		res1 = res;
	}
	return (res * sign);
}

void	destroy(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
	while (i < data->philos[0].philo_nmb)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

int	ft_usleep(size_t time, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (simulation_died(philo) && philo)
			return (1);
		usleep(500);
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "time_error\n", 11);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
