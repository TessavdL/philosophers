/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think_repeat.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/22 14:42:28 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/07/05 13:24:08 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	eat(t_philosopher *phil)
{
	if (sem_wait(phil->forks))
		exit(ERROR_FAILED_TO_LOCK_SEMAPHORE);
	if (*phil->dead == TRUE)
		return (1);
	print_message("has taken a fork ⑂", phil);
	if (sem_wait(phil->forks))
		exit(ERROR_FAILED_TO_LOCK_SEMAPHORE);
	if (*phil->dead == TRUE)
		return (1);
	print_message("is eating 🍝", phil);
	phil->number_of_meals_eaten++;
	phil->time_of_last_meal = get_time();
	usleep(phil->time_it_takes_to_eat * 1000);
	if (sem_post(phil->forks))
		exit(ERROR_FAILED_TO_UNLOCK_SEMAPHORE);
	if (sem_post(phil->forks))
		exit(ERROR_FAILED_TO_UNLOCK_SEMAPHORE);
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
			&& phil->number_of_meals_eaten >= phil->total_number_of_meals))
		return ;
	print_message("is sleeping 💤", phil);
	usleep(phil->time_it_takes_to_sleep * 1000);
}

void	eat_sleep_think_repeat(t_philosopher *phil)
{
	pthread_t	dead_thread;

	if (pthread_create(&dead_thread, NULL, &check_philosopher_status, phil))
		exit(ERROR_FAILED_TO_CREATE_THREAD);
	pthread_detach(dead_thread);
	while (1)
	{
		eat_sleep_think(phil);
		if (*phil->dead == TRUE || (phil->total_number_of_meals != UNINITIALIZED
				&& phil->number_of_meals_eaten >= phil->total_number_of_meals))
			exit(0);
	}
}
