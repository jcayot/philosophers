/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 22:17:25 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/18 22:17:29 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	wait_philosophers(int n, t_philosopher *philosopher)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(philosopher[i].thread, NULL);
		pthread_detach(philosopher[i].thread);
		i++;
	}
}

int	run_philosophers(int n, t_philosopher *philosophers)
{
	int	i;
	struct timeval	start_time;

	i = 0;
	gettimeofday(&start_time, NULL);
	while (i < n)
	{
		philosophers[i].start_time = start_time;
		if (pthread_create(&(philosophers[i].thread), NULL,
				&ft_philosopher, &philosophers[i]) != 0)
		{
			wait_philosophers(i, philosophers);
			return (0);
		}
		i++;
	}
	wait_philosophers(n, philosophers);
	return (1);
}
