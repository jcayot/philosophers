/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 22:17:09 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/18 22:17:12 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*clear_philosophers(int n, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(philosophers[i].left_fork);
		free(philosophers[i].left_fork);
		philosophers[i].left_fork = NULL;
		philosophers[i].right_fork = NULL;
		i++;
	}
	free(philosophers);
	return (0);
}

t_philosopher	*make_philosophers(t_philo_arg arg, int *dead)
{
	t_philosopher	*philosophers;
	int				i;

	philosophers = malloc(arg.n_philos * sizeof (t_philosopher));
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < arg.n_philos)
	{
		philosophers[i].number = i;
		philosophers[i].dead = dead;
		philosophers[i].left_fork = malloc(sizeof (pthread_mutex_t));
		if (!philosophers[i].left_fork)
			return (clear_philosophers(i, philosophers));
		if (pthread_mutex_init(philosophers[i].left_fork, NULL) != 0)
		{
			free(philosophers[i].left_fork);
			return (clear_philosophers(i, philosophers));
		}
		if (i != 0)
			philosophers[i - 1].right_fork = philosophers[i].left_fork;
		i++;
	}
	if (i > 0)
		philosophers[i - 1].right_fork = philosophers[0].left_fork;
	return (philosophers);
}

int	philosophers(int n, char *args[])
{
	t_philo_arg		arg;
	t_philosopher	*philosophers;
	int				dead;
	int				result;

	arg = parse_arguments(n, args);
	if (arg.n_philos < 1)
		return (EXIT_FAILURE);
	dead = 0;
	philosophers = make_philosophers(arg, &dead);
	if (!philosophers)
		return (EXIT_FAILURE);
	result = run_philosophers(arg.n_philos, philosophers);
	clear_philosophers(arg.n_philos, philosophers);
	return (result);
}

int	main(int n, char *args[])
{
	return (philosophers(n, args));
}
