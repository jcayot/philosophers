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

void	ft_eat(t_philosopher *philosopher)
{
	if (philosopher -> number % 2 == 0)
		pthread_mutex_lock(philosopher->left_fork);
	else
		pthread_mutex_lock(philosopher->right_fork);
	print_status(philosopher->number, "has taken a fork", philosopher->dead, getmstime());
	if (philosopher -> number % 2 == 0)
		pthread_mutex_lock(philosopher->right_fork);
	else
		pthread_mutex_lock(philosopher->left_fork);
	print_status(philosopher->number, "has taken a fork", philosopher->dead, getmstime());
	print_status(philosopher->number, "is eating", philosopher->dead, getmstime());
	usleep(philosopher -> rules.eat_time * 1000);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
}

void	ft_sleep(t_philosopher *philosopher)
{
	print_status(philosopher->number, "is sleeping", philosopher->dead, getmstime());
	usleep(philosopher -> rules.sleep_time * 1000);
}

void	ft_think(t_philosopher *philosopher)
{
	print_status(philosopher->number, "is thinking", philosopher->dead, getmstime());
}

void	*ft_philosopher(void *philo_ptr)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *) philo_ptr;
	while (!*philosopher -> dead)
	{
		ft_eat(philosopher);
		ft_sleep(philosopher);
		ft_think(philosopher);
	}
	return (NULL);
}
