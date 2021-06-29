/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_simulation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 11:09:09 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/28 10:17:32 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

static int	create_threads(t_philosopher *philosophers,
	int number_of_philosophers)
{
	int			i;
	pthread_t	dead_thread;

	i = 0;
	while (i < number_of_philosophers)
	{
		philosophers[i].time_of_last_meal = get_time();
		if (pthread_create(&philosophers[i].philosopher, NULL,
				&eat_sleep_think_repeat, &philosophers[i]))
			return (ERROR_FAILED_TO_CREATE_THREAD);
		// usleep(500);
		if (pthread_create(&dead_thread, NULL,
				&check_philosopher_status, &philosophers[i]))
			return (ERROR_FAILED_TO_CREATE_THREAD);
		if (pthread_detach(dead_thread))
			return (ERROR_FAILED_TO_DETACH_THREAD);
		i++;
	}
	return (0);
}

int	start_simulation(t_philosopher *philosophers, int number_of_philosophers)
{
	if (create_threads(philosophers, number_of_philosophers))
	{
		destroy_mutex_helpers(philosophers[0].dead_mutex,
			philosophers[0].eat_mutex, philosophers[0].print_mutex);
		free_mutex_helpers(philosophers[0].dead_mutex,
			philosophers[0].eat_mutex, philosophers[0].print_mutex, 1);
		destroy_mutex_forks(philosophers, number_of_philosophers);
		free(philosophers[0].dead);
		free(philosophers);
		return (ERROR_FAILED_TO_CREATE_THREAD);
	}
	return (end_simulation(philosophers, number_of_philosophers));
}
