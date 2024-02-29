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

int	is_starving(unsigned long last_meal, unsigned long die_time)
{
	return (get_ms_time() > last_meal + die_time);
}

int	monitoring_loop(t_philosopher *philo)
{
	pthread_mutex_lock(&philo -> eating_mutex);
	while (!is_starving(philo -> last_meal, philo -> rules.die_time))
	{
		pthread_mutex_unlock(&philo -> eating_mutex);
		pthread_mutex_lock(&philo -> dead_mutex);
		pthread_mutex_lock(&philo -> lunch_number_mutex);
		if (*philo -> dead || philo -> rules.lunch_number == 0)
		{
			pthread_mutex_unlock(&philo->lunch_number_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->lunch_number_mutex);
		pthread_mutex_unlock(&philo->dead_mutex);
		usleep(50);
		pthread_mutex_lock(&philo -> eating_mutex);
	}
	pthread_mutex_unlock(&philo -> eating_mutex);
	return (1);
}

void	*monitor_philo(void *philo_ptr)
{
	t_philosopher	*philosopher;
	unsigned long	die_time;

	philosopher = (t_philosopher *) philo_ptr;
	if (monitoring_loop(philosopher))
	{
		die_time = stamp(*philosopher->init);
		pthread_mutex_lock(&philosopher -> dead_mutex);
		if (!*philosopher -> dead)
		{
			*philosopher -> dead = 1;
			printf("%ld %d died\n", die_time, philosopher -> n);
		}
		pthread_mutex_unlock(&philosopher -> dead_mutex);
	}
	else
		pthread_mutex_unlock(&philosopher -> dead_mutex);
	return (NULL);
}

int	make_monitor_thread(pthread_t *thread, t_philosopher *philosopher)
{
	if (pthread_create(thread, NULL, &monitor_philo, philosopher) != 0)
	{
		if (!*philosopher -> dead)
		{
			pthread_mutex_lock(&philosopher -> dead_mutex);
			if (!*philosopher -> dead)
			{
				*philosopher -> dead = 1;
				printf("Error creating thread. Stopping\n");
			}
			pthread_mutex_unlock(&philosopher -> dead_mutex);
		}
		return (0);
	}
	return (1);
}
