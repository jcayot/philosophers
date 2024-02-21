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

static pthread_mutex_t	*new_mutex(void)
{
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof (pthread_mutex_t));
	if (!mutex)
		return (NULL);
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		free(mutex);
		return (NULL);
	}
	return (mutex);
}

int	clear_philosophers(int n, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(philosophers[i].left_fork);
		free(philosophers[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(philosophers->dead_mutex);
	free(philosophers->dead_mutex);
	return (0);
}

int	make_philosophers(t_philo_arg arg, int *dead, t_philosopher *philosophers)
{
	int				i;

	philosophers[0].dead_mutex = new_mutex();
	if (!philosophers -> dead_mutex)
		return (0);
	i = 0;
	while (i < arg.n_philos)
	{
		philosophers[i].number = i;
		philosophers[i].dead = dead;
		philosophers[i].rules = arg.rules;
		philosophers[i].dead_mutex = philosophers[0].dead_mutex;
		philosophers[i].left_fork = new_mutex();
		if (!philosophers[i].left_fork)
			return (clear_philosophers(i, philosophers));
		if (i != 0)
			philosophers[i - 1].right_fork = philosophers[i].left_fork;
		i++;
	}
	if (i > 0)
		philosophers[i - 1].right_fork = philosophers[0].left_fork;
	return (1);
}
