/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_philosophers.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/25 13:58:47 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/07/22 11:41:02 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"
#include "../includes/names.h"

static void	initialize_philosopher(t_input input, t_philosopher *philosopher,
	t_bool *dead, int i)
{
	memset(philosopher, 0, sizeof(*philosopher));
	philosopher->dead = dead;
	philosopher->id = i;
	philosopher->name = (char *)g_names[philosopher->id];
	philosopher->total_number_of_meals = input.number_of_meals;
	philosopher->max_time_between_meals = input.max_time_between_meals;
	philosopher->time_it_takes_to_eat = input.time_it_takes_to_eat;
	philosopher->time_it_takes_to_sleep = input.time_it_takes_to_sleep;
	philosopher->time_start = get_time();
}

t_philosopher	*setup_philosophers(t_input input)
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
		initialize_philosopher(input, &philosophers[i], dead, i);
		i++;
	}
	return (philosophers);
}
