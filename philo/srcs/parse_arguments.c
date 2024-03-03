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

#include "philosophers.h"

t_philo_arg	parse_arguments(int n, char *args[])
{
	t_philo_arg	arg;

	arg.n_philos = -1;
	if (n < 5 || n > 6)
		return (arg);
	arg.rules.die_time = philotoi(args[2]);
	if (arg.rules.die_time < 0)
		return (arg);
	arg.rules.eat_time = philotoi(args[3]);
	if (arg.rules.eat_time < 0)
		return (arg);
	arg.rules.sleep_time = philotoi(args[4]);
	if (arg.rules.sleep_time < 0)
		return (arg);
	if (n == 6)
	{
		arg.rules.lunch_number = philotoi(args[5]);
		if (arg.rules.lunch_number < 0)
			return (arg);
	}
	else
		arg.rules.lunch_number = -1;
	arg.n_philos = philotoi(args[1]);
	return (arg);
}
