/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 08:45:18 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/19 08:45:22 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	clear_mutexs(int n, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&philosophers[i].left_fork);
		pthread_mutex_destroy(&philosophers[i].eating_mutex);
		pthread_mutex_destroy(&philosophers[i].lunch_number_mutex);
		i++;
	}
	pthread_mutex_destroy(&philosophers->dead_mutex);
	return (0);
}

int	make_mutexs(t_philosopher *philosopher)
{
	if (pthread_mutex_init(&philosopher->left_fork, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&philosopher->eating_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philosopher->left_fork);
		return (0);
	}
	if (pthread_mutex_init(&philosopher->lunch_number_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&philosopher->left_fork);
		pthread_mutex_destroy(&philosopher->eating_mutex);
		return (0);
	}
	return (1);
}

int	make_philosophers(t_philo_arg arg, int *dead, t_philosopher *philosophers)
{
	int				i;

	if (pthread_mutex_init(&philosophers[0].dead_mutex, NULL) != 0)
		return (0);
	i = 0;
	while (i < arg.n_philos)
	{
		philosophers[i].n = i;
		philosophers[i].dead = dead;
		philosophers[i].rules = arg.rules;
		philosophers[i].dead_mutex = philosophers[0].dead_mutex;
		if (!make_mutexs(&philosophers[i]))
			return (clear_mutexs(i, philosophers));
		if (i != 0)
			philosophers[i - 1].right_fork = &philosophers[i].left_fork;
		i++;
	}
	philosophers[i - 1].right_fork = &philosophers[0].left_fork;
	return (1);
}
