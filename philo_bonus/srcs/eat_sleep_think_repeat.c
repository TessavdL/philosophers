/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think_repeat.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/22 14:42:28 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/24 13:38:37 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	eat(t_philosopher *phil)
{
	if (sem_wait(phil->forks))
		exit(ERROR_FAILED_TO_LOCK_SEMAPHORE);
	if (sem_wait(phil->forks))
		exit(ERROR_FAILED_TO_LOCK_SEMAPHORE);
	print_message("has taken a fork ⑂", phil);
	print_message("is eating 🍝", phil);
	usleep(phil->time_it_takes_to_eat * 1000);
	phil->number_of_meals_eaten++;
	phil->time_of_last_meal = get_time();
	if (sem_post(phil->forks))
		exit(ERROR_FAILED_TO_UNLOCK_SEMAPHORE);
	if (sem_post(phil->forks))
		exit(ERROR_FAILED_TO_UNLOCK_SEMAPHORE);
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

static void	eat_sleep_think(t_philosopher *phil)
{
	if (check_if_a_philosopher_is_dead(phil))
		return ;
	think(phil);
	if (check_if_a_philosopher_is_dead(phil))
		return ;
	eat(phil);
	if (phil->total_number_of_meals != UNINITIALIZED
		&& phil->number_of_meals_eaten >= phil->total_number_of_meals)
		return ;
	if (check_if_a_philosopher_is_dead(phil))
		return ;
	slep(phil);
	if (check_if_a_philosopher_is_dead(phil))
		return ;
}

void	eat_sleep_think_repeat(t_philosopher *phil)
{
	while (1)
	{
		eat_sleep_think(phil);
		if (*phil->dead == TRUE)
		{
			printf("A philosopher has died\n");
			exit(0);
		}
		if (phil->total_number_of_meals != UNINITIALIZED
			&& phil->number_of_meals_eaten >= phil->total_number_of_meals)
		{
			printf("%s is done eating\n", phil->name);
			exit(0);
		}
	}
}
