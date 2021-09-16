/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think_repeat.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 13:33:10 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/09/16 18:06:47 by tessa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

static int	eat(t_philosopher *phil)
{
	pthread_mutex_lock(&phil->fork_left);
	if (*phil->dead == TRUE)
	{
		pthread_mutex_unlock(&phil->fork_left);
		return (1);
	}
	print_message("has taken a fork ⑂", phil);
	pthread_mutex_lock(phil->fork_right);
	if (*phil->dead == TRUE)
	{
		pthread_mutex_unlock(&phil->fork_left);
		pthread_mutex_unlock(phil->fork_right);
		return (1);
	}
	print_message("is eating 🍝", phil);
	phil->time_of_last_meal = get_time();
	phil->number_of_meals_eaten++;
	usleep(phil->time_it_takes_to_eat * 1000);
	pthread_mutex_unlock(&phil->fork_left);
	pthread_mutex_unlock(phil->fork_right);
	return (0);
}

static void	eat_sleep_think(t_philosopher *phil)
{
	if (*phil->dead == TRUE)
		return ;
	print_message("is thinking 💡", phil);
	if (eat(phil))
		return ;
	if (*phil->dead == TRUE || (phil->total_number_of_meals != UNINITIALIZED
		&& check_if_philosopher_is_full(phil) == TRUE))
		return ;
	print_message("is sleeping 💤", phil);
	usleep(phil->time_it_takes_to_sleep * 1000);
}

void	*eat_sleep_think_repeat(void *philosopher)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)philosopher;
	while (1)
	{
		eat_sleep_think(phil);
		if (*phil->dead == TRUE || (phil->total_number_of_meals != UNINITIALIZED
			&& check_if_philosopher_is_full(phil) == TRUE))
			break ;
	}
	return (NULL);
}
