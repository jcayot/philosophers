//
// Created by jules on 23/02/2024.
//

#include <philo_utils.h>

unsigned long get_ms_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
