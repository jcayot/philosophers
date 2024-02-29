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

int	run_one_philosopher(int die_time)
{
	printf("0 has taken a fork\n");
	stupid_sleep(die_time);
	printf("0 died\n");
	return (EXIT_SUCCESS);
}

int	run_philosophers(int n, t_philosopher *philosophers)
{
	int				i;
	unsigned long	start_time;

	i = 0;
	start_time = get_ms_time();
	while (i < n)
	{
		philosophers[i].init = &start_time;
		if (pthread_create(&(philosophers[i].thread), NULL,
				&philosopher_thread, &philosophers[i]) != 0)
		{
			*philosophers -> dead = 1;
			wait_philosophers(i, philosophers);
			return (0);
		}
		i++;
	}
	wait_philosophers(n, philosophers);
	return (1);
}
