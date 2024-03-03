/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stupid_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:00:15 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/23 14:00:17 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

void	stupid_sleep(unsigned long mstime)
{
	unsigned long	start;

	start = get_ms_time();
	while ((get_ms_time() - start) < mstime)
		usleep(500);
}
