/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_log.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:39:20 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/24 12:39:21 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	philo_log(int n, char *status, const int *dead, unsigned long time)
{
	if (!*dead)
		printf("%lu %d %s\n", time, n, status);
}
