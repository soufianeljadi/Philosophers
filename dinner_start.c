/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:19:59 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/10/07 15:33:29 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eats(t_philosopher *philo)
{
	t_table *table;

	table = philo->table;
	pthread_mutex_lock(&(table->forks[philo->left_fork_id]));
	action_print(table, philo->id, "has taken a fork");
	pthread_mutex_lock(&(table->forks[philo->right_fork_id]));
	action_print(table, philo->id, "has taken a fork");
	pthread_mutex_lock(&(table->meal_check));
	action_print(table, philo->id, "is eating");
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(table->meal_check));
	smart_sleep(table->time_to_eat, table);
	(philo->x_ate)++;
	pthread_mutex_unlock(&(table->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(table->forks[philo->right_fork_id]));
}

void	*p_thread(void *void_philosopher)
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

void	exit_launcher(t_table *table, t_philosopher *philos)
{
	int i;

	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_mutex_destroy(&(table->forks[i]));
	pthread_mutex_destroy(&(table->writing));
}

void	death_checker(t_table *r, t_philosopher *p)
{
	int i;

	while (!(r->all_ate))
	{
		i = -1;
		while (++i < r->philo_nbr && !(r->dieded))
		{
			pthread_mutex_lock(&(r->meal_check));
			if (time_diff(p[i].t_last_meal, timestamp()) > r->time_to_die)
			{
				action_print(r, i, "died");
				r->dieded = 1;
			}
			pthread_mutex_unlock(&(r->meal_check));
			usleep(100);
		}
		if (r->dieded)
			break ;
		i = 0;
		while (r->max_meals != -1 && i < r->philo_nbr && p[i].x_ate >= r->max_meals)
			i++;
		if (i == r->philo_nbr)
			r->all_ate = 1;
	}
}

int		dinner_start(t_table *table)
{
	int				i;
	t_philosopher	*phi;

	i = 0;
	phi = table->philosophers;
	table->first_timestamp = timestamp();
	while (i < table->philo_nbr)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, p_thread, &(phi[i])))
			return (1);
		phi[i].t_last_meal = timestamp();
		i++;
	}
	death_checker(table, table->philosophers);
	exit_launcher(table, phi);
	return (0);
}
