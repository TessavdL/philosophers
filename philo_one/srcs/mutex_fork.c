/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_fork.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 17:39:04 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/26 14:46:37 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

static void	set_pointer_to_right_fork(t_philosopher **philosophers,
	int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers - 1)
	{
		(*philosophers)[i].fork_right = &((*philosophers)[i + 1]).fork_left;
		i++;
	}
	(*philosophers)[i].fork_right = &((*philosophers)[0]).fork_left;
}

int	destroy_mutex_forks(t_philosopher *philosophers, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_mutex_destroy(&philosophers[i].fork_left);
		i++;
	}
	return (0);
}

static int	destroy_forks_part(t_philosopher *philosophers, int i)
{
	while (i > 0)
	{
		i--;
		pthread_mutex_destroy(&philosophers[i].fork_left);
	}
	return (0);
}

int	initiliaze_forks(t_philosopher **philosophers, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_mutex_init(&((*philosophers)[i]).fork_left, NULL))
		{
			destroy_forks_part(&((*philosophers)[i]), i);
			return (-1);
		}
		i++;
	}
	set_pointer_to_right_fork(philosophers, number_of_philosophers);
	return (0);
}
