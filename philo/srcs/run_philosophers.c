/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 22:17:25 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/18 22:17:29 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_philosophers(int n, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(philosophers[i].thread, NULL);
		pthread_detach(philosophers[i].thread);
		i++;
	}
}

int	monitor_philosophers(int n, t_philosopher *philosophers)
{
	unsigned long	die_time;
	int				i;

	while (1)
	{
		i = 0;
		while (i < n)
		{
			pthread_mutex_lock(&philosophers[i].eating_mutex);
			if (philosophers[i].rules.lunch_number != 0
				&& is_starving(philosophers[i].last_meal, philosophers[i].rules.die_time))
			{
				die_time = stamp(*philosophers[i].init);
				pthread_mutex_lock(&philosophers[i].dead_mutex);
				*philosophers[i].dead = 1;
				printf("%ld %d died\n", die_time, i);
				pthread_mutex_unlock(&philosophers[i].dead_mutex);
				pthread_mutex_unlock(&philosophers[i].eating_mutex);
				return (1);
			}
			pthread_mutex_unlock(&philosophers[i].eating_mutex);
			i++;
		}
		i = 0;
		while (i < n)
		{
			pthread_mutex_lock(&philosophers[i].eating_mutex);
			if (philosophers[i].rules.lunch_number != 0)
			{
				pthread_mutex_unlock(&philosophers[i].eating_mutex);
				break ;
			}
			pthread_mutex_unlock(&philosophers[i].eating_mutex);
			if (i == n - 1)
				return (1);
			i++;
		}
		usleep(50);
	}
	return (0);
}

int	run_philosophers(int n, t_philosopher *philosophers)
{
	int				i;
	unsigned long	start_time;

	i = 0;
	start_time = get_ms_time();
	while (i < n)
	{
		philosophers[i].init = &start_time;
		philosophers[i].last_meal = start_time;
		if (pthread_create(&(philosophers[i].thread), NULL,
				&philosopher_thread, &philosophers[i]) != 0)
		{
			*philosophers -> dead = 1;
			wait_philosophers(i, philosophers);
			return (0);
		}
		i++;
	}
	monitor_philosophers(n, philosophers);
	wait_philosophers(n, philosophers);
	return (1);
}
