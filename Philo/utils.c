/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jadi <sel-jadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:19:50 by sel-jadi          #+#    #+#             */
/*   Updated: 2024/10/14 22:17:41 by sel-jadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			s;
	long int	r;
	long int	x;

	(1) && (i = 0, s = 1, r = 0);
	if (!str[0])
		return (-1);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		s = 44 - str[i++];
	while (str[i] >= '0' && str[i] <= '9')
	{
		x = r * 10 + (str[i++] - 48);
		if (r > x && s == 1)
			return (-1);
		else if (r > x && s == -1)
			return (0);
		r = x;
	}
	if (str[i] != '\0')
		return (-1);
	return (r * s);
}

// 1 second = 1000 milliseconds
// 1 millisecond = 1000 microseconds
long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	smart_sleep(long long time, t_table *table)
{
	long long	i;

	i = timestamp();
	while (!(table->dieded))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

void	action_print(t_table *table, int id, char *string)
{
	pthread_mutex_lock(&(table->writing));
	if (!(table->dieded))
	{
		printf("%lli ", timestamp() - table->first_timestamp);
		printf("%i ", id + 1);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(table->writing));
	return ;
}
