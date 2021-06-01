/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 13:33:10 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/01 12:59:27 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	eat_sleep_think(t_philo *phil)
{
	pthread_mutex_lock(&phil->fork);
	pthread_mutex_lock(phil->fork_next);
	printf("%s %d has taken a fork\n", "timestamp_in_ms", phil->i);
	usleep(100);
	printf("%s %d is eating\n", "timestamp_in_ms", phil->i);
	phil->n_eat++;
	pthread_mutex_unlock(&phil->fork);
	pthread_mutex_unlock(phil->fork_next);
	printf("%s %d is sleeping\n", "timestamp_in_ms", phil->i);
	usleep(100);
	printf("%s %d is thinking\n", "timestamp_in_ms", phil->i);
}
