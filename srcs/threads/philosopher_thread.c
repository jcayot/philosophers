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

#include <philosophers.h>

void	ft_eat_even(t_philosopher *philo)
{
	pthread_mutex_lock(philo -> left_fork);
	philo_log(philo, "has taken a fork");
	if (philo -> right_fork)
	{
		pthread_mutex_lock(philo -> right_fork);
		philo_log(philo, "has taken a fork");
		pthread_mutex_lock(philo -> eating_mutex);
		if (!*philo -> dead)
		{
			philo -> last_meal = get_ms_time();
			philo_log(philo, "is eating");
			pthread_mutex_unlock(philo -> eating_mutex);
			stupid_sleep(philo -> rules.eat_time);
		}
		pthread_mutex_unlock(philo -> right_fork);
	}
	else
	{
		while (!*philo -> dead)
			;
	}
	pthread_mutex_unlock(philo -> left_fork);
}

void	ft_eat_odd(t_philosopher *philo)
{
	pthread_mutex_lock(philo -> right_fork);
	philo_log(philo, "has taken a fork");
	pthread_mutex_lock(philo -> left_fork);
	philo_log(philo, "has taken a fork");
	pthread_mutex_lock(philo -> eating_mutex);
	if (!*philo -> dead)
	{
		philo -> last_meal = get_ms_time();
		philo_log(philo, "is eating");
		pthread_mutex_unlock(philo -> eating_mutex);
		stupid_sleep(philo -> rules.eat_time);
	}
	pthread_mutex_unlock(philo -> left_fork);
	pthread_mutex_unlock(philo -> right_fork);
}

void	ft_sleep(t_philosopher *philo)
{
	philo_log(philo, "is sleeping");
	stupid_sleep(philo -> rules.sleep_time);
}

void	philosopher_routine(t_philosopher *philo)
{
	while (!*philo -> dead
		&& (philo->rules.lunch_number == -1 || philo->rules.lunch_number > 0))
	{
		if (philo -> n % 2 != 0)
			usleep(50);
		if (philo -> n % 2 == 0)
			ft_eat_even(philo);
		else
			ft_eat_odd(philo);
		ft_sleep(philo);
		philo_log(philo, "is thinking");
		if (philo->rules.lunch_number != -1)
			philo->rules.lunch_number--;
	}
}

void	*philosopher_thread(void *philo_ptr)
{
	t_philosopher	*philo;
	pthread_t		monitor_thread;

	philo = (t_philosopher *) philo_ptr;
	while (*philo->start == 0)
	{
		if (*philo->dead)
			return (NULL);
	}
	philo -> last_meal = *philo -> init;
	if (!make_monitor_thread(&monitor_thread, philo))
		return (NULL);
	philosopher_routine(philo);
	return (NULL);
}
