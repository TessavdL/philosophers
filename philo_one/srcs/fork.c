/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 17:39:04 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/03 12:09:36 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

static void	fork_assign(t_philo *philosophers, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo - 1)
	{
		philosophers[i].fork_next = &philosophers[i + 1].fork;
		i++;
	}
	philosophers[i].fork_next = &philosophers[0].fork;
}

int	fork_destroy(t_philo *philosophers, int n_philo)
{
	int i;

	i = 0;	
	while (i < n_philo)
	{
		if (pthread_mutex_destroy(&philosophers[i].fork))
			return (-1);
		i++;
	}
	return (0);
}

static int	fork_destroy_part(t_philo *philosophers, int i)
{
	while (i > 0)
	{
		i--;
		if (pthread_mutex_destroy(&philosophers[i].fork))
			return (-1);
	}
	return (0);
}

int	fork_init(t_philo *philosophers, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_mutex_init(&philosophers[i].fork, NULL))
		{
			fork_destroy_part(&philosophers[i], i);
			return (-1);
		}
		i++;
	}
	fork_assign(philosophers, n_philo);
	return (0);
}
