
#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		(printf("Invalid arguments number !"), exit(EXIT_FAILURE));
	parse_input(&table, av);
	data_init(&table);
	dinner_start(&table); //philos full | 1 philo died
	return (0);
}
