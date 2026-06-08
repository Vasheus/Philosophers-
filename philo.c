/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 08:24:15 by yosabir           #+#    #+#             */
/*   Updated: 2024/12/27 15:37:27 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if ((str[i] == '+' || str[i] == '-') && (str[i + 1] < '0'
			|| str[i + 1] > '9'))
		return (1);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

int	input_check(char ac, char **av)
{
	int	num;

	num = ft_atoi(av[1]);
	if (num <= 0 || num > 200 || check(av[1]))
		return (1);
	num = ft_atoi(av[2]);
	if (num < 60 || check(av[2]))
		return (1);
	num = ft_atoi(av[3]);
	if (num < 60 || check(av[3]))
		return (1);
	num = ft_atoi(av[4]);
	if (num < 60 || check(av[4]))
		return (1);
	if (ac == 6)
	{
		num = ft_atoi(av[5]);
		if (num <= 0 || check(av[5]))
			return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if ((ac != 5 && ac != 6))
		return (printf("syntax error\n"), 1);
	if (input_check(ac, av) == 1)
		return (1);
	init(&data, philos, forks, av);
	init_philos(philos, &data, forks, av);
	threads(&data, forks);
	destroy(&data, forks);
	return (0);
}
