/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 22:18:08 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/18 22:18:11 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_UTILS_H
# define PHILO_UTILS_H

# include <limits.h>
# include <sys/time.h>
# include <stdlib.h>

int		philotoi(char *s);
long getmststamp(struct timeval startime);

#endif //PHILO_UTILS_H
