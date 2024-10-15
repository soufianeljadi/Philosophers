/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:19:28 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/10/15 16:12:22 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		return (printf("Invalid arguments number !"));
	if ((init_data(&table, av)) == -1)
		return (printf("Wrong arguments !"));
	else if ((init_data(&table, av)) == -2)
		return (printf("Error intializing mutex"));
	if (dinner_start(&table))
		return (printf("Error creating threads"));
	return (0);
}
