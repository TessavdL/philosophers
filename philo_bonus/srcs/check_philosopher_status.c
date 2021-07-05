/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_philosopher_status.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/05 11:09:53 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/07/05 13:23:26 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

t_bool	check_if_philosopher_is_full(t_philosopher *phil)
{
	if (phil->number_of_meals_eaten == phil->total_number_of_meals)
		return (TRUE);
	return (FALSE);
}

static t_bool	check_if_this_philosopher_is_dead(t_philosopher *phil)
{
	long long	time;
	long long	time_between_meals;

	time = (long long)get_time();
	time_between_meals = time - (long long)phil->time_of_last_meal;
	if (time_between_meals >= (long long)phil->max_time_between_meals)
		return (TRUE);
	return (FALSE);
}

static t_bool	check_if_a_philosopher_is_dead(t_philosopher **phil)
{
	if (sem_wait((*phil)->dead_semaphore))
		exit(ERROR_FAILED_TO_LOCK_SEMAPHORE);
	if (*(*phil)->dead == TRUE)
	{
		if (sem_post((*phil)->dead_semaphore))
			exit(ERROR_FAILED_TO_UNLOCK_SEMAPHORE);
		return (TRUE);
	}
	if (check_if_this_philosopher_is_dead(*phil))
	{
		print_message("is dead 💀", *phil);
		*(*phil)->dead = TRUE;
		if (sem_post((*phil)->dead_semaphore))
			exit(ERROR_FAILED_TO_UNLOCK_SEMAPHORE);
		return (TRUE);
	}
	if (sem_post((*phil)->dead_semaphore))
		exit(ERROR_FAILED_TO_UNLOCK_SEMAPHORE);
	return (FALSE);
}

void	*check_philosopher_status(void *philosopher)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)philosopher;
	while (1)
	{
		if (check_if_a_philosopher_is_dead(&phil))
		{
			kill(phil->philosopher, SIGTERM);
			return (NULL);
		}
		if (phil->total_number_of_meals != UNINITIALIZED
			&& check_if_philosopher_is_full(phil) == TRUE)
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
