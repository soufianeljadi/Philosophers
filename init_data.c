/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:20:05 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/10/14 13:56:59 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	not_empty(char *av)
{
	int	i;

	i = 0;
	if (av[i] == '\0')
		return(1);
	while(av[i])
	{
		if(av[i] != ' ' && av[i] != '\t')
			return (1);// 1 means not empty
		i++;
	}
	return(0);
}

int	init_mutex(t_table *table)
{
	int i;

	i = table->philo_nbr;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(table->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(table->meal_check), NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_table *table)
{
	int i;

	i = table->philo_nbr;
	while (--i >= 0)
	{
		table->philosophers[i].id = i;
		table->philosophers[i].meal_nbr = 0;
		table->philosophers[i].left_fork_id = i;
		table->philosophers[i].right_fork_id = (i + 1) % table->philo_nbr;
		table->philosophers[i].t_last_meal = 0;
		table->philosophers[i].table = table;
	}
	return (0);
}

int	init_data(t_table *table, char **argv)
{
	table->philo_nbr = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->all_ate = 0;
	table->dieded = 0;
	if (/*table->philo_nbr < 2|| */ table->time_to_die < 0 || table->time_to_eat < 0
		|| table->time_to_sleep < 0 || table->philo_nbr > 250)
		(printf("Wrong arguments !"), exit(EXIT_FAILURE));
	if (argv[5] && not_empty(argv[5]))
	{
		table->max_meals = ft_atoi(argv[5]);
		if (table->max_meals <= 0)
			(printf("Wrong arguments !"), exit(EXIT_FAILURE));
	}
	else
		table->max_meals = -1;
	if (init_mutex(table))
		return (1);
	init_philosophers(table);
	return (0);
}
