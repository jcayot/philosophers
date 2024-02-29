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
	pthread_mutex_unlock(&philo -> eating_mutex);
	philo_log(philo, "is eating");
	stupid_sleep(philo -> rules.eat_time);
	pthread_mutex_unlock(philo -> right_fork);
	pthread_mutex_unlock(&philo -> left_fork);
}

void	ft_sleep(t_philosopher *philo)
{
	philo_log(philo, "is sleeping");
	stupid_sleep(philo -> rules.sleep_time);
}

void	philosopher_routine(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->lunch_number_mutex);
	while (!*philo -> dead
		&& (philo->rules.lunch_number == -1 || philo->rules.lunch_number > 0))
	{
		pthread_mutex_unlock(&philo->lunch_number_mutex);
		if (philo -> n % 2 != 0)
			usleep(50);
		ft_eat(philo);
		ft_sleep(philo);
		philo_log(philo, "is thinking");
		pthread_mutex_lock(&philo->lunch_number_mutex);
		if (philo->rules.lunch_number != -1)
			philo->rules.lunch_number--;
	}
	pthread_mutex_unlock(&philo->lunch_number_mutex);
}

void	*philosopher_thread(void *philo_ptr)
{
	t_philosopher	*philo;
	pthread_t		monitor_thread;

	philo = (t_philosopher *) philo_ptr;
	philo -> last_meal = *philo -> init;
	if (!make_monitor_thread(&monitor_thread, philo))
		return (NULL);
	philosopher_routine(philo);
	pthread_join(monitor_thread, NULL);
	return (NULL);
}
