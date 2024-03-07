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

#include "philosophers.h"

int	one_philosopher(int die_time)
{
	printf("0 has taken a fork\n");
	stupid_sleep(die_time);
	printf("0 died\n");
	return (EXIT_SUCCESS);
}

int	parsing_error(void)
{
	printf("Error invalid syntax.\n\n");
	printf("Usage : \n");
	printf("./philo ");
	printf("number_of_philosophers time_to_die time_to_eat time_to_sleep");
	printf(" (optional) number_of_times_each_philosopher_must_eat\n\n");
	printf("All arguments must be positive integers.\n");
	return (EXIT_FAILURE);
}

int	philosophers(int n, char *args[])
{
	t_philo_arg		arg;
	t_philosopher	*philosophers;
	int				dead;
	int				result;

	arg = parse_arguments(n, args);
	if (arg.n_philos < 1)
		return (parsing_error());
	else if (arg.n_philos == 1)
		return (one_philosopher(arg.rules.die_time));
	dead = 0;
	philosophers = malloc((arg.n_philos) * sizeof (t_philosopher));
	if (!philosophers)
		return (EXIT_FAILURE);
	result = EXIT_FAILURE;
	if (make_philosophers(arg, &dead, philosophers))
	{
		result = run_philosophers(arg.n_philos, philosophers);
		clear_mutexs(arg.n_philos, philosophers);
	}
	free(philosophers);
	return (result);
}

int	main(int n, char *args[])
{
	return (philosophers(n, args));
}
