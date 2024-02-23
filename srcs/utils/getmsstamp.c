/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getmsstamp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:46:20 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/21 14:46:22 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_utils.h>

unsigned long getmsstamp(struct timeval startime)
{
	struct timeval	time;
	unsigned long	timestamp;

	gettimeofday(&time, NULL);
	timestamp = (time.tv_sec - startime.tv_sec) * 1000lu;
	timestamp += (long) ((long) time.tv_usec - (long) startime.tv_usec) / 1000l;
	return (timestamp);
}
