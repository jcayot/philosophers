/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:01:24 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/23 14:01:26 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int is_starving(struct timeval last_meal, long die_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (last_meal.tv_sec * 1000000 + last_meal.tv_usec + die_time * 1000 <
				time.tv_sec * 1000000 + time.tv_usec);
}

void	*monitor_philo(void *philo_ptr)
{
	t_philosopher	*philosopher;
	long 			die_time;

	philosopher = (t_philosopher *) philo_ptr;
	while (!is_starving(philosopher -> last_meal, philosopher -> rules.die_time))
	{
		if (*philosopher -> dead)
			return (NULL);
	}
	die_time = getmsstamp(*philosopher->start_time);
	pthread_mutex_lock(philosopher -> dead_mutex);
	if (!*philosopher -> dead)
	{
		*philosopher -> dead = 1;
		printf("%ld %d died\n", die_time, philosopher -> number);
	}
	pthread_mutex_unlock(philosopher -> dead_mutex);
	return (NULL);
}

int	make_monitor_thread(pthread_t *thread, t_philosopher *philosopher)
{
	if (pthread_create(thread, NULL, &monitor_philo, philosopher) != 0)
	{
		if (!*philosopher -> dead)
		{
			pthread_mutex_lock(philosopher -> dead_mutex);
			if (!*philosopher -> dead)
			{
				*philosopher -> dead = 1;
				printf("Error creating thread. Stopping\n");
			}
			pthread_mutex_unlock(philosopher -> dead_mutex);
		}
		return (0);
	}
	return (1);
}
