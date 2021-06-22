/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end_simulation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 17:39:04 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/22 12:35:57 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

static int	wait_for_simulation_to_terminate(t_philosopher *philosophers,
	int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_join(philosophers[i].philosopher, NULL))
			return (-1);
		i++;
	}
	return (0);
}

int	end_simulation(t_philosopher *philosophers, int number_of_philosophers)
{
	if (wait_for_simulation_to_terminate(philosophers, number_of_philosophers))
	{
		pthread_mutex_destroy(philosophers[0].print_mutex);
		free(philosophers[0].dead);
		free(philosophers);
		destroy_forks(philosophers, number_of_philosophers);
		return (ERROR_FAILED_TO_JOIN_THREADS);
	}
	pthread_mutex_destroy(philosophers[0].print_mutex);
	free(philosophers[0].dead);
	free(philosophers);
	destroy_forks(philosophers, number_of_philosophers);
	return (0);
}
