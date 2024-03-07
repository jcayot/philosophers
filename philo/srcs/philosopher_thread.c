/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 22:16:27 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/18 22:16:33 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_log(t_philosopher *philo, char *status)
{
	unsigned long	time;

	time = stamp(*philo -> init);
	pthread_mutex_lock(philo -> dead_mutex);
	if (!(*philo -> dead))
		printf("%lu %d %s\n", time, philo->n, status);
	pthread_mutex_unlock(philo -> dead_mutex);
}

void	ft_eat(t_philosopher *philo)
{
	if (philo -> n % 2 == 0)
		pthread_mutex_lock(&philo -> left_fork);
	else
		pthread_mutex_lock(philo -> right_fork);
	philo_log(philo, "has taken a fork");
	if (philo -> n % 2 == 0)
		pthread_mutex_lock(philo -> right_fork);
	else
		pthread_mutex_lock(&philo -> left_fork);
	philo_log(philo, "has taken a fork");
	pthread_mutex_lock(&philo -> eating_mutex);
	philo -> last_meal = get_ms_time();
	philo_log(philo, "is eating");
	if (philo->rules.lunch_number > 0)
		philo->rules.lunch_number--;
	pthread_mutex_unlock(&philo -> eating_mutex);
	stupid_sleep(philo -> rules.eat_time);
	pthread_mutex_unlock(philo -> right_fork);
	pthread_mutex_unlock(&philo -> left_fork);
}

void	*philosopher_thread(void *philo_ptr)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) philo_ptr;
	pthread_mutex_lock(philo -> dead_mutex);
	while (!(*philo -> dead))
	{
		pthread_mutex_unlock(philo -> dead_mutex);
		if (philo -> n % 2 != 0)
			usleep(50);
		ft_eat(philo);
		philo_log(philo, "is sleeping");
		stupid_sleep(philo -> rules.sleep_time);
		philo_log(philo, "is thinking");
		if (philo -> n % 2 == 0)
			usleep(50);
		pthread_mutex_lock(philo -> dead_mutex);
	}
	pthread_mutex_unlock(philo -> dead_mutex);
	return (NULL);
}
