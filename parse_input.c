/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:11:33 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/27 20:19:50 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// 5 — The number of philosophers
// 800 — The time a philosopher will die if he doesn’t eat
// 200 — The time it takes a philosopher to eat
// 200 — The time it takes a philosopher to sleep
// 7 — Nbr of times all the philos need to eat before terminating the program
// ** optional argument
int	not_empty(char *av)
{
	int	i;

	i = 0;
	(void)av;
	// if (av[i] == '\0')
	// 	return(1);
	// while(av[i])
	// {
	// 	if(av[i] != ' ' || av[i] != '\t')
	// 		return (1);
	// 	i++;
	// }
	return(0);
}

void	parse_input(t_table *table, char **av)
{
	table->philo_nbr = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]) * 1000;
	table->time_to_eat = ft_atoi(av[3]) * 1000;
	table->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (table->time_to_die < 60000
		|| table->time_to_eat < 60000
		|| table->time_to_sleep < 60000
		|| av[5][0] == '\0'
		|| (av[5] && not_empty(av[5])))
		(printf("INVALID ARGUMENT !\n\
1) Use timestamps major than 60ms!\n\
2) Dont use non-digit caracteres!\n\
REMEMBER:\n\
1 argument : The number of philosophers\n\
2 argument : The time a philosopher will die if he doesnt eat\n\
3 argument : The time it takes a philosopher to eat\n\
4 argument : The time it takes a philosopher to sleep\n\
5 argument (optional): Nbr of times all the philos need to eat\n"), exit(EXIT_FAILURE));
	// if (av[5] && !not_empty(av[5]))
	// 	table->max_meals = ft_atoi(av[5]);
	// else
	// 	table->max_meals = -1;
}
