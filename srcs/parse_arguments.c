/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 22:16:51 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/18 22:16:55 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

t_philo_arg	parse_arguments(int n, char *args[])
{
	t_philo_arg	arg;

	arg.n_philos = -1;
	if (n < 5 || n > 6)
		return (arg);
	arg.die_time = philotoi(args[2]);
	if (arg.die_time < 0)
		return (arg);
	arg.eat_time = philotoi(args[3]);
	if (arg.eat_time < 0)
		return (arg);
	arg.sleep_time = philotoi(args[4]);
	if (arg.sleep_time < 0)
		return (arg);
	if (n == 6)
	{
		arg.lunch_number = philotoi(args[5]);
		if (arg.lunch_number < 0)
			return (arg);
	}
	else
		arg.lunch_number = 0;
	arg.n_philos = philotoi(args[1]);
	return (arg);
}
