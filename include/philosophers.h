/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 22:18:34 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/18 22:18:37 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <philo_utils.h>

typedef struct s_philosophers_arg
{
	int	n_philos;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	lunch_number;
}	t_philo_arg;

typedef struct s_philosopher
{
	pthread_t		thread;
	int				number;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				*dead;
}	t_philosopher;

t_philo_arg		parse_arguments(int n, char *args[]);
int				run_philosophers(int n, t_philosopher *philosophers);
void			*ft_philosopher(void *philo_ptr);

#endif //PHILOSOPHERS_H
