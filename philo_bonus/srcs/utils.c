/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 12:17:29 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/07/05 12:05:22 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval	tv;
	unsigned long	seconds;
	unsigned long	microseconds;

	gettimeofday(&tv, NULL);
	seconds = tv.tv_sec * 1000;
	microseconds = tv.tv_usec / 1000;
	return (seconds + microseconds);
}

void	print_message(char *message, t_philosopher *phil)
{
	unsigned long	time_elapsed;

	if (sem_wait(phil->print_semaphore))
		exit(ERROR_FAILED_TO_LOCK_SEMAPHORE);
	time_elapsed = get_time() - phil->time_start;
	printf("[%.4lu] %d %s\n", time_elapsed, phil->id, message);
	if (sem_post(phil->print_semaphore))
		exit(ERROR_FAILED_TO_UNLOCK_SEMAPHORE);
}
