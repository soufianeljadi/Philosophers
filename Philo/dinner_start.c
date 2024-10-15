/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:19:59 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/10/15 20:41:21 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eats(t_philosopher *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&(table->forks[philo->left_fork_id]));
	action_print(table, philo->id, "has taken a fork");
	pthread_mutex_lock(&(table->forks[philo->right_fork_id]));
	action_print(table, philo->id, "has taken a fork");
	action_print(table, philo->id, "is eating");
	pthread_mutex_lock(&(table->meal_check));
	philo->t_last_meal = timestamp();
	(philo->meal_nbr)++;
	pthread_mutex_unlock(&(table->meal_check));
	smart_sleep(table->time_to_eat, table);
	pthread_mutex_unlock(&(table->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(table->forks[philo->right_fork_id]));
}

void	*actions(void *void_philosopher)
{
	int				i;
	t_philosopher	*philo;
	t_table			*table;

	i = 0;
	philo = (t_philosopher *)void_philosopher;
	table = philo->table;
	if (philo->id % 2)
		usleep(table->time_to_eat);
	while (1)
	{
		if (table->philo_nbr == 1)
		{
			pthread_mutex_lock(&(table->forks[philo->left_fork_id]));
			action_print(table, philo->id, "has taken a fork");
			pthread_mutex_unlock(&(table->forks[philo->left_fork_id]));
			break ;
		}
		philo_eats(philo);
		action_print(table, philo->id, "is sleeping");
		smart_sleep(table->time_to_sleep, table);
		action_print(table, philo->id, "is thinking");
	}
	return (NULL);
}

void	exit_dinner(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
		pthread_mutex_destroy(&(table->forks[i]));
	pthread_mutex_destroy(&(table->writing));
	pthread_mutex_destroy(&(table->meal_check));
}

void	death_checker(t_table *table, t_philosopher *p)
{
	int	i;

	while (!(table->all_ate))
	{
		i = -1;
		while (++i < table->philo_nbr && !(table->dieded))
		{
			pthread_mutex_lock(&(table->meal_check));
			if (time_diff(p[i].t_last_meal, timestamp()) > table->time_to_die)
			{
				pthread_mutex_lock(&table->writing);
				printf("%lli ", timestamp() - table->first_timestamp);
				printf("%i ", i + 1);
				printf("%s\n", "died");
				return ;
			}
			pthread_mutex_unlock(&(table->meal_check));
			usleep(100);
		}
		if (table->dieded)
			break ;
		if (table->max_meals && check_ate(table, p))
			break ;
	}
}

int	dinner_start(t_table *table)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	philo = table->philosophers;
	table->first_timestamp = timestamp();
	while (i < table->philo_nbr)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, actions, &(philo[i])))
			return (1);
		pthread_detach(philo[i].thread_id);
		pthread_mutex_lock(&(table->meal_check));
		philo[i].t_last_meal = timestamp();
		pthread_mutex_unlock(&(table->meal_check));
		i++;
	}
	death_checker(table, table->philosophers);
	exit_dinner(table);
	return (0);
}
