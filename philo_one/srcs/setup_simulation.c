/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_simulation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/25 14:00:55 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/26 14:59:53 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int	setup_simulation(t_input input)
{
	t_philosopher	*philosophers;

	philosophers = setup_philosophers(input);
	if (!philosophers)
		return (ERROR_MALLOC_FAILED);
	if (initialize_mutex_helpers(input.number_of_philosophers, philosophers))
	{
		free(philosophers[0].dead);
		free(philosophers);
		return (ERROR_FAILED_TO_INITIALIZE_MUTEX_HELPERS);
	}
	if (initiliaze_forks(&philosophers, input.number_of_philosophers))
	{
		destroy_mutex_helpers(philosophers[0].dead_mutex,
			philosophers[0].eat_mutex, philosophers[0].print_mutex);
		free_mutex_helpers(philosophers[0].dead_mutex,
			philosophers[0].eat_mutex, philosophers[0].print_mutex, 1);
		free(philosophers[0].dead);
		free(philosophers);
		return (ERROR_FAILED_TO_INITIALIZE_FORKS);
	}
	return (start_simulation(philosophers, input.number_of_philosophers));
}
