/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 13:33:10 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/03 22:50:10 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

static bool	check_if_dead(t_philo *phil) 
{
	if (*phil->dead == true)
		return (true);
	if (check_dead_timer(phil))
	{
		*phil->dead = true;
		printf("%lu %d is dead 💀\n", get_time(), phil->i);
		return (true);
	}
	return (false);
}

static void	eat(t_philo *phil)
{
	pthread_mutex_lock(&phil->fork);
	pthread_mutex_lock(phil->fork_next);
	if (*phil->dead == true)
	{
		pthread_mutex_unlock(&phil->fork);
		pthread_mutex_unlock(phil->fork_next);
		return ;
	}
	printf("%lu %d has taken a fork %s\n", get_time(), phil->i, "\u2442");
	printf("%lu %d is eating 🍝\n", get_time(), phil->i);
	phil->timer.last_eaten = get_time();
	phil->n_eat++;
	usleep(phil->timer.eat * 1000);
	pthread_mutex_unlock(&phil->fork);
	pthread_mutex_unlock(phil->fork_next);
}

static void	slep(t_philo *phil)
{
	printf("%lu %d is sleeping 💤\n", get_time(), phil->i);
	usleep(phil->timer.sleep * 1000);
}

static void	think(t_philo *phil)
{
	printf("%lu %d is thinking 💡\n", get_time(), phil->i);
}

void	eat_sleep_think(t_philo *phil)
{
	if (check_if_dead(phil))
		return ;
	eat(phil);
	if (check_if_dead(phil))
		return ;
	slep(phil);
	if (check_if_dead(phil))
		return ;
	think(phil);
	if (check_if_dead(phil))
		return ;
}

void	*eat_sleep_think_repeat(void *philosopher)
{
	t_philo *phil;

	phil = ((t_philo*)philosopher);
	while (1)
	{
		eat_sleep_think(phil);
		if (*phil->dead == true)
		{
			// printf("Phil is dead\n");
			break ;
		}
		if (phil->n_eat >= phil->total_eat)
		{
			// printf("Phil is full\n");
			break ;
		}
	}
	return (NULL);
}
