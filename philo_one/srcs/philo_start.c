/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_start.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 11:09:09 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/01 13:24:06 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

static int	philo_join(t_dlist *philosophers)
{
	t_dlist	*temp;
	t_philo	*phil;

	temp = philosophers;
	while (temp->next)
	{
		phil = ((t_philo*)temp->content);
		if (pthread_join(phil->philosopher, NULL))
			return (-1);
		temp = temp->next;
	}
	return (0);
}

static void *philo_create(void *philosopher)
{
	t_philo	*phil;

	phil = ((t_philo*)philosopher);
	while (phil->n_eat < phil->total_eat)
	{
		eat_sleep_think(phil);
	}
	return (NULL);
}

static int	philo_init(t_dlist **philosophers, t_input input)
{
	int				i;
	unsigned long	time;
	t_philo			*phil;

	time = get_time();
	i = 0;
	while (i < input.n_philo)
	{
		phil = malloc(sizeof(t_philo));
		if (!phil)
			return (free_philosophers_and_return(*philosophers));
		memset(phil, 0, sizeof(*phil));
		phil->i = i + 1;
		phil->total_eat = input.n_eat;
		phil->total_philo = input.n_philo;
		phil->timer = &input.timer;
		phil->timer->start = time;
		dlist_add_back(philosophers, dlist_new(phil));
		i++;
	}
	if (fork_init(*philosophers))
		return (free_philosophers_and_return(*philosophers));
	return (0);
}

int	philo_start(t_input input)
{
	t_dlist	*temp;
	t_dlist	*philosophers;
	t_philo *phil;

	philosophers = NULL;
	if (philo_init(&philosophers, input))
		return (-1);
	temp = philosophers;
	while (temp)
	{
		phil = ((t_philo*)temp->content);
		if (pthread_create(&phil->philosopher, NULL, &philo_create, phil))
		{
			printf("Create\n");
			return (free_philosophers_and_return(philosophers));
		}
		temp = temp->next;
	}
	if (philo_join(philosophers))
	{
		printf("Join\n");
		return (free_philosophers_and_return(philosophers));
	}
	for (temp = philosophers; temp; temp = temp->next)
		printf("n eat = %d\n", ((t_philo*)temp->content)->n_eat);
	if (fork_destroy(dlist_last(philosophers)))
	{
		printf("Destroy\n");
		return (free_philosophers_and_return(philosophers));
	}
	dlist_delete_all(&philosophers, free);
	return (0);
}
