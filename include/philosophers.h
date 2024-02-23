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

# include <stdio.h>
# include <pthread.h>
# include <philo_utils.h>

typedef struct s_rules
{
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	lunch_number;
}	t_rules;

typedef struct s_philosophers_arg
{
	int		n_philos;
	t_rules	rules;
}	t_philo_arg;

typedef struct s_philosopher
{
	pthread_t		thread;
	int				number;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				*dead;
	pthread_mutex_t	*dead_mutex;
	t_rules			rules;
	struct timeval	last_meal;
	struct timeval	*start_time;
	int 			*start;
}	t_philosopher;

t_philo_arg	parse_arguments(int n, char *args[]);
int			make_philosophers(t_philo_arg arg, int *dead,
				t_philosopher *philosophers);
int			clear_philosophers(int n, t_philosopher *philosophers);
int			run_philosophers(int n, t_philosopher *philosophers);
void		*ft_philosopher(void *philo_ptr);
int			make_monitor_thread(pthread_t *thread, t_philosopher *philosopher);
void		print_status(int n, char *status, const int *dead, unsigned long time);

#endif //PHILOSOPHERS_H
