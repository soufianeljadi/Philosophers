/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:19:59 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/10/13 20:19:33 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eats(t_philosopher *philo)
{
	t_table *table;

	table = philo->table;
	//lock left fork
	pthread_mutex_lock(&(table->forks[philo->left_fork_id]));
	action_print(table, philo->id, "has taken a fork");
	//lock right fork
	pthread_mutex_lock(&(table->forks[philo->right_fork_id]));
	action_print(table, philo->id, "has taken a fork");
	//start eating
	action_print(table, philo->id, "is eating");
	//save time after meal and unlock it 
	pthread_mutex_lock(&(table->meal_check));
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(table->meal_check));
	//sleep time to eat
	smart_sleep(table->time_to_eat, table);
	//increment meal nbr
	(philo->meal_nbr)++;
	//unlock forks 
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
		usleep(15000);
	while (!(table->dieded))
	{
		if (table->philo_nbr == 1)
		{
			pthread_mutex_lock(&(table->forks[philo->left_fork_id]));
			action_print(table, philo->id, "has taken a fork");
			pthread_mutex_unlock(&(table->forks[philo->left_fork_id]));
			break;
		}
		philo_eats(philo);
		if (table->all_ate)
			break ;
		action_print(table, philo->id, "is sleeping");
		smart_sleep(table->time_to_sleep, table);
		action_print(table, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	exit_dinner(t_table *table, t_philosopher *philos)
{
	int i;

	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_mutex_destroy(&(table->forks[i]));
	pthread_mutex_destroy(&(table->writing));
	pthread_mutex_destroy(&(table->meal_check));
}

void	death_checker(t_table *table, t_philosopher *p)
{
	int i;

	while (!(table->all_ate))
	{
		i = -1;
		while (++i < table->philo_nbr && !(table->dieded))
		{
			pthread_mutex_lock(&(table->meal_check));
			if (time_diff(p[i].t_last_meal, timestamp()) > table->time_to_die) //time past without eating
			{
				action_print(table, i, "died");
				table->dieded = 1;
				// pthread_mutex_unlock(&(table->meal_check));
				// return ;
			}
			pthread_mutex_unlock(&(table->meal_check));
			usleep(100);
		}
		if (table->dieded)
			break ;
		i = 0;
		while (table->max_meals != -1 && i < table->philo_nbr && p[i].meal_nbr >= table->max_meals)
			i++;
		if (i == table->philo_nbr)
			table->all_ate = 1;
	}
}

int		dinner_start(t_table *table)
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
			pthread_mutex_lock(&(table->meal_check));
			philo[i].t_last_meal = timestamp();
			pthread_mutex_unlock(&(table->meal_check));
		i++;
	}
	death_checker(table, table->philosophers);
	exit_dinner(table, philo);
	return (0);
}
