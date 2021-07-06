/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_helpers.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/25 10:34:56 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/26 14:58:51 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	destroy_mutex_helpers(pthread_mutex_t *dead_mutex,
	pthread_mutex_t *eat_mutex, pthread_mutex_t *print_mutex)
{
	pthread_mutex_destroy(dead_mutex);
	pthread_mutex_destroy(eat_mutex);
	pthread_mutex_destroy(print_mutex);
}

int	free_mutex_helpers(pthread_mutex_t *dead_mutex, pthread_mutex_t *eat_mutex,
	pthread_mutex_t *print_mutex, int ret)
{
	free(dead_mutex);
	free(eat_mutex);
	free(print_mutex);
	return (ret);
}

static void	assign_mutexes(pthread_mutex_t **dead_mutex,
	pthread_mutex_t **eat_mutex, pthread_mutex_t **print_mutex,
	t_philosopher *philosopher)
{
	philosopher->dead_mutex = *dead_mutex;
	philosopher->eat_mutex = *eat_mutex;
	philosopher->print_mutex = *print_mutex;
}

static int	initialize_mutex_helpers_continued(pthread_mutex_t **dead_mutex,
	pthread_mutex_t **eat_mutex, pthread_mutex_t **print_mutex)
{
	if (pthread_mutex_init(*dead_mutex, NULL))
		return (ERROR_FAILED_TO_INITIALIZE_MUTEX_HELPERS);
	if (pthread_mutex_init(*eat_mutex, NULL))
	{
		pthread_mutex_destroy(*dead_mutex);
		return (ERROR_FAILED_TO_INITIALIZE_MUTEX_HELPERS);
	}
	if (pthread_mutex_init(*print_mutex, NULL))
	{
		pthread_mutex_destroy(*dead_mutex);
		pthread_mutex_destroy(*eat_mutex);
		return (ERROR_FAILED_TO_INITIALIZE_MUTEX_HELPERS);
	}
	return (0);
}

int	initialize_mutex_helpers(int number_of_philosophers,
	t_philosopher *philosophers)
{
	int				i;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	*print_mutex;

	dead_mutex = malloc(sizeof(pthread_mutex_t));
	if (!dead_mutex)
		return (ERROR_MALLOC_FAILED);
	eat_mutex = malloc(sizeof(pthread_mutex_t));
	if (!eat_mutex)
		return (free_mutex_helpers(dead_mutex, NULL, NULL, 1));
	print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!print_mutex)
		return (free_mutex_helpers(dead_mutex, eat_mutex, NULL, 1));
	if (initialize_mutex_helpers_continued(&dead_mutex, &eat_mutex,
			&print_mutex))
		return (free_mutex_helpers(dead_mutex, eat_mutex, print_mutex, 2));
	i = 0;
	while (i < number_of_philosophers)
	{
		assign_mutexes(&dead_mutex, &eat_mutex, &print_mutex, &philosophers[i]);
		i++;
	}
	return (0);
}
