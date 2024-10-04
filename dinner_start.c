
#include "philosophers.h"

void	*dinner_simulation(void *data)
{
	// (void)data;
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->max_meals == 0)
		return ;
	else if (table-> philo_nbr == 1)
		puts("there's only one philosopher");
	else
	{
		while (++i < table->philo_nbr)
			pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation,
				table->philos[i]);
	}
	return ;
	// now all threads ready
}
