/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 13:33:10 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/22 12:34:05 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

static void	eat(t_philosopher *phil)
{
	pthread_mutex_lock(&phil->fork_left);
	if (*phil->dead == TRUE)
	{
		pthread_mutex_unlock(&phil->fork_left);
		return ;
	}
	print_message("has taken a fork ⑂", phil);
	pthread_mutex_lock(phil->fork_right);
	if (*phil->dead == TRUE)
	{
		pthread_mutex_unlock(&phil->fork_left);
		pthread_mutex_unlock(phil->fork_right);
		return ;
	}
	print_message("is eating 🍝", phil);
	phil->time_of_last_meal = get_time();
	phil->number_of_meals_eaten++;
	usleep(phil->time_it_takes_to_eat * 1000);
	pthread_mutex_unlock(&phil->fork_left);
	pthread_mutex_unlock(phil->fork_right);
}

static void	slep(t_philosopher *phil)
{
	print_message("is sleeping 💤", phil);
	usleep(phil->time_it_takes_to_sleep * 1000);
}

static void	think(t_philosopher *phil)
{
	print_message("is thinking 💡", phil);
}

void	eat_sleep_think(t_philosopher *phil)
{
	if (check_if_a_philosopher_is_dead(phil))
		return ;
	think(phil);
	if (check_if_a_philosopher_is_dead(phil))
		return ;
	eat(phil);
	if (check_if_a_philosopher_is_dead(phil))
		return ;
	slep(phil);
	if (check_if_a_philosopher_is_dead(phil))
		return ;
}

void	*eat_sleep_think_repeat(void *philosopher)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)philosopher;
	while (1)
	{
		eat_sleep_think(phil);
		if (*phil->dead == TRUE)
			break ;
		if (phil->total_number_of_meals != UNINITIALIZED
			&& phil->number_of_meals_eaten >= phil->total_number_of_meals)
			break ;
	}
	return (NULL);
}
