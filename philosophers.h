/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:19:41 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/10/08 14:23:45 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <stdio.h>
# include <limits.h>

struct s_table;

//philo data
typedef	struct			s_philosopher
{
	int					id;
	int					meal_nbr;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	pthread_t			thread_id;
	struct s_table		*table; //The t_table structure holds global simulation parameters and shared resources, such as:
}						t_philosopher;

//global data 
typedef struct			s_table
{
	int					philo_nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meals;
	int					dieded;
	int					all_ate;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		writing;
	t_philosopher		philosophers[250];
}						t_table;

int						write_error(char *str);

int						init_data(t_table *table, char **argv);

int						ft_atoi(const char *str);
void					action_print(t_table *table, int id, char *string);
long long				timestamp(void);
long long				time_diff(long long past, long long pres);
void					smart_sleep(long long time, t_table *table);

int						dinner_start(t_table *table);
void					exit_dinner(t_table *table, t_philosopher *philos);

#endif
