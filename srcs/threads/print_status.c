//
// Created by jules on 23/02/2024.
//

#include <philosophers.h>

void print_status(int n, char *status, const int *dead, unsigned long time)
{
	if (!*dead)
		printf("%lu %d %s\n", time, n, status);
}
