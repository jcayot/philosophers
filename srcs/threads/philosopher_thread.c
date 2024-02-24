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
	pthread_mutex_lock(philo->left_fork);
	philo_log(philo->n, "has taken a fork", philo->dead, stamp(*philo->init));
	if (philo -> right_fork)
	{
		pthread_mutex_lock(philo->right_fork);
		philo_log(philo->n, "has taken a fork", philo->dead,
			stamp(*philo->init));
		pthread_mutex_lock(philo -> eating_mutex);
		if (!*philo -> dead)
		{
			philo -> last_meal = get_ms_time();
			philo_log(philo->n, "is eating", philo->dead, stamp(*philo->init));
			stupid_sleep(philo -> rules.eat_time);
		}
		pthread_mutex_unlock(philo -> eating_mutex);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		while (!*philo->dead)
			;
	}
	pthread_mutex_unlock(philo->left_fork);
}

void	ft_eat_odd(t_philosopher *philo)
{
	pthread_mutex_lock(philo -> right_fork);
	philo_log(philo->n, "has taken a fork", philo->dead, stamp(*philo->init));
	pthread_mutex_lock(philo->left_fork);
	philo_log(philo->n, "has taken a fork", philo->dead, stamp(*philo->init));
	pthread_mutex_lock(philo -> eating_mutex);
	if (!*philo -> dead)
	{
		philo -> last_meal = get_ms_time();
		philo_log(philo->n, "is eating", philo->dead, stamp(*philo->init));
		stupid_sleep(philo -> rules.eat_time);
	}
	pthread_mutex_unlock(philo -> eating_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philosopher *philo)
{
	philo_log(philo->n, "is sleeping", philo->dead, stamp(*philo->init));
	stupid_sleep(philo -> rules.sleep_time);
}

void	ft_think(t_philosopher *philo)
{
	philo_log(philo->n, "is thinking", philo->dead, stamp(*philo->init));
	stupid_sleep(1);
}

void	*philosopher_thread(void *philo_ptr)
{
	t_philosopher	*philosopher;
	pthread_t		monitor_thread;

	philosopher = (t_philosopher *) philo_ptr;
	while (*philosopher->start == 0)
	{
		if (*philosopher->dead)
			return (NULL);
	}
	philosopher -> last_meal = *philosopher -> init;
	if (!make_monitor_thread(&monitor_thread, philosopher))
		return (NULL);
	if (philosopher -> n % 2 != 0)
		stupid_sleep(1);
	while (!*philosopher -> dead)
	{
		if (philosopher -> n % 2 == 0)
			ft_eat_even(philosopher);
		else
			ft_eat_odd(philosopher);
		ft_sleep(philosopher);
		ft_think(philosopher);
	}
	return (NULL);
}
