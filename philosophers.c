/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:01:47 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/07/26 16:21:39 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		(printf("Invalid arguments number !"), exit(EXIT_FAILURE));
	parse_input(&table, av);
	data_init(&table);
	// dinner_start(&table);
		//philos full | 1 philo died
	// cleanup(&table);
	return (0);
}
