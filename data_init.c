
#include "philosophers.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	// Odd
	if (philo->id % 2)
	{
		philo->first_fork = &forks[philo_position]; // Right fork
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr]; // Left fork (wrap around)
	}
	// even
	philo->first_fork = &forks[(philo_position + 1) % philo_nbr]; // Left fork
	philo->second_fork = &forks[philo_position];// Right fork
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals = 0;
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end = false;
	table->all_ready = false;
	//Allocate Memory for Philosophers
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		(printf("Malloc failed!"), exit(EXIT_FAILURE));
	// Global mutex
	// pthread_mutex_init(&table->table_mutex, NULL);
	// Allocate Memory for Forks
	table->forks = malloc(sizeof(t_fork) * table->philo_nbr);
	if (!table->forks)
		(printf("Malloc failed!"), exit(EXIT_FAILURE));
	//Initialize Each Fork's Mutex
	while (++i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
