/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 22:16:27 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/18 22:16:33 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void print_status(int n, char *status, const int *dead, long time)
{
	if (!*dead)
		printf("%ld %d %s\n", time, n, status);
}

void	ft_eat(t_philosopher *philo)
{
	if (philo -> number % 2 == 0)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	print_status(philo->number, "has taken a fork", philo->dead, getmststamp(philo->start_time));
	if (philo -> number % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	print_status(philo->number, "has taken a fork", philo->dead, getmststamp(philo->start_time));
	gettimeofday(&philo -> last_meal, NULL);
	print_status(philo->number, "is eating", philo->dead, getmststamp(philo->start_time));
	usleep(philo -> rules.eat_time * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philosopher *philo)
{
	print_status(philo->number, "is sleeping", philo->dead, getmststamp(philo->start_time));
	usleep(philo -> rules.sleep_time * 1000);
}

void	ft_think(t_philosopher *philo)
{
	print_status(philo->number, "is thinking", philo->dead, getmststamp(philo->start_time));
}

void	*ft_philosopher(void *philo_ptr)
{
	t_philosopher	*philosopher;
	pthread_t		monitor_thread;

	philosopher = (t_philosopher *) philo_ptr;
	philosopher -> last_meal = philosopher -> start_time;
	if (pthread_create(&monitor_thread, NULL, &monitor_philo, philosopher) != 0)
		return (NULL);
	while (!*philosopher -> dead)
	{
		ft_eat(philosopher);
		ft_sleep(philosopher);
		ft_think(philosopher);
	}
	return (NULL);
}
