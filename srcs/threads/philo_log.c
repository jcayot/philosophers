/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_log.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:39:20 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/24 12:39:21 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	philo_log(t_philosopher *philo, char *status)
{
	pthread_mutex_lock(philo -> dead_mutex);
	if (!*philo -> dead)
		printf("%lu %d %s\n", stamp(*philo -> init), philo -> n, status);
	pthread_mutex_unlock(philo -> dead_mutex);
}
