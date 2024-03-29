/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philotoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 22:17:44 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/18 22:17:47 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

int	philotoi(char *s)
{
	long	n;

	if (*s == '+')
		s++;
	if (*s < '0' || *s > '9')
		return (-1);
	n = 0;
	while (*s >= '0' && *s <= '9')
	{
		n = (n * 10) + (*s - '0');
		if (n > (long) INT_MAX)
			return (-1);
		s++;
	}
	if (*s)
		return (-1);
	return ((int) n);
}
