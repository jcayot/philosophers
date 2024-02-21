/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getmstime.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:46:20 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/21 14:46:22 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_utils.h>

long	getmstime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long) (time.tv_sec * 1000) + (long) (time.tv_usec / 1000));
}
