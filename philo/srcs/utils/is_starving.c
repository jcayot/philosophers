/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_starving.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:16:26 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/04 16:16:30 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_utils.h>

int	is_starving(unsigned long last_meal, unsigned long die_time)
{
	return (get_ms_time() > last_meal + die_time);
}
