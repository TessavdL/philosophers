/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_start.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 11:09:09 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/03 22:53:46 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

static void *check_for_dead(void *dead)
{
	bool	*dead_check;

	dead_check = (bool*)dead;
	while (1)
	{
		if (*dead_check == true)
		{
			printf("Phil detected dead\n");
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}

static int	philo_join(t_philo *philosophers, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_join(philosophers[i].philosopher, NULL))
			return (-1);
		i++;
	}
	return (0);
}

static t_philo	*philo_init(t_input input)
{
	int		i;
	t_philo *philosophers;

	philosophers = malloc(sizeof(t_philo) * input.n_philo);
	if (!philosophers)
		return (NULL);
	i = 0;
	while (i < input.n_philo)
	{
		memset(&philosophers[i], 0, sizeof(philosophers[i]));
		philosophers[i].i = i + 1;
		philosophers[i].total_eat = input.n_eat;
		philosophers[i].timer.death = input.timer.death;
		philosophers[i].timer.eat = input.timer.eat;
		philosophers[i].timer.sleep = input.timer.sleep;
		i++;
	}
	if (fork_init(philosophers, input.n_philo))
	{
		free(philosophers);
		return (NULL);
	}
	return (philosophers);
}

int	philo_start(t_input input)
{
	pthread_t dead_thread;
	bool	dead;
	int		i;
	t_philo	*philosophers;

	dead = false;
	philosophers = philo_init(input);
	if (!philosophers)
		return (-1);
	pthread_create(&dead_thread, NULL, &check_for_dead, &dead);
	i = 0;
	while (i < input.n_philo)
	{
		philosophers[i].dead = &dead;
		philosophers[i].timer.last_eaten = get_time();
		if (pthread_create(&philosophers[i].philosopher, NULL, &eat_sleep_think_repeat, &philosophers[i]))
		{
			printf("Create\n");
			free(philosophers);
			return (-1);
		}
		i++;
	}
	pthread_detach(dead_thread);
	if (philo_join(philosophers, input.n_philo))
	{
		printf("Join\n");
		fork_destroy(philosophers, input.n_philo);
		free(philosophers);
		return (-1);
	}
	for (i = 0; i < input.n_philo; i++)
		printf("Phil %d has eaten %d times\n", i, philosophers[i].n_eat);
	if (fork_destroy(philosophers, input.n_philo))
	{
		printf("Destroy\n");
		free(philosophers);
		return (-1);
	}
	free(philosophers);
	return (0);
}
