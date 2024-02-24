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

void	ft_eat(t_philosopher *philo)
{
	if (philo -> number % 2 == 0)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	print_status(philo->number, "has taken a fork",
		philo->dead, get_ms_stamp(*philo->start_time));
	if (philo -> number % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	print_status(philo->number, "has taken a fork",
		philo->dead, get_ms_stamp(*philo->start_time));
	pthread_mutex_lock(philo -> eating_mutex);
	if (!*philo -> dead)
	{
		philo -> last_meal = get_ms_time();
		print_status(philo->number, "is eating",
			philo->dead, get_ms_stamp(*philo->start_time));
		stupid_sleep(philo -> rules.eat_time);
	}
	pthread_mutex_unlock(philo -> eating_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philosopher *philo)
{
	print_status(philo->number, "is sleeping", philo->dead,
		get_ms_stamp(*philo->start_time));
	stupid_sleep(philo -> rules.sleep_time);
}

void	ft_think(t_philosopher *philo)
{
	print_status(philo->number, "is thinking", philo->dead,
		get_ms_stamp(*philo->start_time));
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
	philosopher -> last_meal = *philosopher -> start_time;
	if (!make_monitor_thread(&monitor_thread, philosopher))
		return (NULL);
	if (philosopher -> number % 2 != 0)
		stupid_sleep(1);
	while (!*philosopher -> dead)
	{
		ft_eat(philosopher);
		ft_sleep(philosopher);
		ft_think(philosopher);
	}
	return (NULL);
}
