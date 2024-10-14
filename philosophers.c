/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:19:28 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/10/14 22:18:01 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		(printf("Invalid arguments number !"), exit(EXIT_FAILURE));
	if ((init_data(&table, av)))
		(printf("Error intializing mutex"), exit(EXIT_FAILURE));
	if (dinner_start(&table))
		(printf("Error creating threads"), exit(EXIT_FAILURE));
	return (0);
}
