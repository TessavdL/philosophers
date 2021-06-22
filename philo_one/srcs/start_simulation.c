/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_simulation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 11:09:09 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/22 12:23:08 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"
#include "../includes/names.h"

static int	create_threads(t_philosopher *philosophers,
	int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		philosophers[i].time_of_last_meal = philosophers[i].time_start;
		if (pthread_create(&philosophers[i].philosopher, NULL,
				&eat_sleep_think_repeat, &philosophers[i]))
			return (-1);
		i++;
	}
	return (0);
}

static int	start_simulation(t_philosopher *philosophers,
	int number_of_philosophers)
{
	if (create_threads(philosophers, number_of_philosophers))
	{
		pthread_mutex_destroy(philosophers[0].print_mutex);
		free(philosophers[0].dead);
		free(philosophers);
		destroy_forks(philosophers, number_of_philosophers);
		return (ERROR_FAILED_TO_CREATE_THREAD);
	}
	return (end_simulation(philosophers, number_of_philosophers));
}

static void	initialize_philosopher(t_input input, t_philosopher *philosopher,
	pthread_mutex_t *print_mutex, t_bool *dead)
{
	static int	i = 0;

	memset(philosopher, 0, sizeof(*philosopher));
	philosopher->dead = dead;
	philosopher->print_mutex = print_mutex;
	philosopher->id = i;
	philosopher->name = (char *)names[philosopher->id];
	philosopher->total_number_of_meals = input.number_of_meals;
	philosopher->max_time_between_meals = input.max_time_between_meals;
	philosopher->time_it_takes_to_eat = input.time_it_takes_to_eat;
	philosopher->time_it_takes_to_sleep = input.time_it_takes_to_sleep;
	philosopher->time_start = get_time();
	i++;
}

static t_philosopher	*initialize_philosophers(t_input input,
	pthread_mutex_t *print_mutex)
{
	int				i;
	t_bool			*dead;
	t_philosopher	*philosophers;

	philosophers = malloc(sizeof(t_philosopher) * input.number_of_philosophers);
	if (!philosophers)
		return (NULL);
	dead = malloc(sizeof(t_bool));
	if (!dead)
	{
		free(philosophers);
		return (NULL);
	}
	*dead = FALSE;
	i = 0;
	while (i < input.number_of_philosophers)
	{
		initialize_philosopher(input, &philosophers[i], print_mutex, dead);
		i++;
	}
	return (philosophers);
}

int	setup_simulation(t_input input)
{
	t_philosopher	*philosophers;
	pthread_mutex_t	print_mutex;

	if (pthread_mutex_init(&print_mutex, NULL))
		return (ERROR_FAILED_TO_INITIALIZE_PRINT_MUTEX);
	philosophers = initialize_philosophers(input, &print_mutex);
	if (!philosophers)
	{
		pthread_mutex_destroy(&print_mutex);
		return (ERROR_MALLOC_FAILED);
	}
	if (initiliaze_forks(philosophers, input.number_of_philosophers))
	{
		pthread_mutex_destroy(philosophers[0].print_mutex);
		free(philosophers[0].dead);
		free(philosophers);
		return (ERROR_FAILED_TO_INITIALIZE_FORKS);
	}
	return (start_simulation(philosophers, input.number_of_philosophers));
}
