/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stamp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:46:20 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/21 14:46:22 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_utils.h>

unsigned long	stamp(unsigned long startime)
{
	return (get_ms_time() - startime);
}
