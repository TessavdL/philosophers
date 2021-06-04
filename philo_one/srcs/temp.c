/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   temp.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/03 09:09:24 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/03 12:09:42 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/philo_one.h"

// static void *philo_create(void *philosopher)
// {
// 	t_philo *phil;

// 	phil = ((t_philo*)philosopher);
// 	while (1)
// 	{
// 		eat_sleep_think(phil);
// 		if (*phil->dead == true)
// 			break ;
// 		if (phil->n_eat == phil->total_eat)
// 			break ;
// 	}
// 	return (NULL);
// }

// static int	philo_join(t_philo *philosophers, int n_philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < n_philo)
// 	{
// 		if (pthread_join(&philosophers[i].philosopher, NULL))
// 			return (-1);
// 		i++;
// 	}
// 	return (0);
// }

// static int	philo_init(t_philo *philosophers, t_input input)
// {
// 	int		i;

// 	philosophers = malloc(sizeof(t_philo) * input.n_philo);
// 	if (!philosophers)
// 		return (-1);
// 	i = 0;
// 	while (i < input.n_philo)
// 	{
// 		memset(&philosophers[i], 0, sizeof(philosophers[i]));
// 		philosophers[i].i = i + 1;
// 		philosophers[i].total_eat = input.n_eat;
// 		philosophers[i].total_philo = input.n_philo;
// 		philosophers[i].timer.death = input.timer.death;
// 		philosophers[i].timer.eat = input.timer.eat;
// 		philosophers[i].timer.sleep = input.timer.sleep;
// 		i++;
// 	}
// 	fork_init(philosophers, input.n_philo);
// 	return (0);
// }

// int	philo_start(t_input input)
// {
// 	bool	*dead;
// 	int		i;
// 	t_philo	*philosophers;

// 	dead = malloc(sizeof(bool));
// 	if (!dead)
// 		return (-1);
// 	philosophers = NULL;
// 	if (philo_init(&philosophers, input))
// 		return (-1);
// 	i = 0;
// 	while (i < input.n_eat)
// 	{
// 		philosophers[i].timer.last_eaten = get_time();
// 		philosophers[i].dead = dead;
// 		if (pthread_create(&philosophers[i].philosopher, NULL, &philo_create, philosophers[i]))
// 		{
// 			printf("Create\n");
// 			free(philosophers);
// 			free(dead);
// 			return (-1);
// 		}
// 		i++;
// 	}
// 	if (philo_join(philosophers))
// 	{
// 		printf("Join\n");
// 		free(philosophers);
// 		free(dead);
// 		return (-1);
// 	}
// 	for (i = 0; i < input.n_philo; i++)
// 		printf("n eat = %d\n", philosophers[i].n_eat);
// 	if (fork_destroy(philosophers, input.n_philo))
// 	{
// 		printf("Destroy\n");
// 		free(philosophers);
// 		free(dead);
// 		return (-1);
// 	}
// 	free(philosophers);
// 	free(dead);
// 	return (0);
// }



// // static int	philo_detach(t_dlist *philosophers)
// // {
// // 	t_dlist	*temp;
// // 	t_philo	*phil;

// // 	temp = philosophers;
// // 	while (temp->next)
// // 	{
// // 		phil = ((t_philo*)temp->content);
// // 		if (pthread_detach(phil->philosopher))
// // 			return (-1);
// // 		temp = temp->next;
// // 	}
// // 	return (0);
// // }

// static int	philo_join(t_dlist *philosophers)
// {
// 	t_dlist	*temp;
// 	t_philo	*phil;

// 	temp = philosophers;
// 	while (temp->next)
// 	{
// 		phil = ((t_philo*)temp->content);
// 		if (pthread_join(phil->philosopher, NULL))
// 			return (-1);
// 		temp = temp->next;
// 	}
// 	return (0);
// }

// static void *philo_create(void *philosopher)
// {
// 	t_dlist	*list;
// 	t_philo *phil;

// 	list = ((t_dlist*)philosopher);
// 	phil = ((t_philo*)list->content);
// 	while (1)
// 	{
// 		eat_sleep_think(phil);
// 		if (*phil->dead == true)
// 		{
// 			break ;
// 		}
// 		if (phil->n_eat == phil->total_eat)
// 			break ;
// 	}
// 	return (NULL);
// }

// static int	philo_init(t_dlist **philosophers, t_input input)
// {
// 	int				i;
// 	bool			*dead;
// 	t_philo			*phil;

// 	i = 0;
// 	dead = malloc(sizeof(bool));
// 	if (!dead)
// 		return (-1);
// 	*dead = false;
// 	while (i < input.n_philo)
// 	{
// 		phil = malloc(sizeof(t_philo));
// 		if (!phil)
// 			return (free_philosophers_and_return(*philosophers));
// 		memset(phil, 0, sizeof(*phil));
// 		phil->i = i + 1;
// 		phil->total_eat = input.n_eat;
// 		phil->total_philo = input.n_philo;
// 		phil->timer.death = input.timer.death;
// 		phil->timer.eat = input.timer.eat;
// 		phil->timer.sleep = input.timer.sleep;
// 		phil->start = *philosophers;
// 		phil->dead = dead;
// 		dlist_add_back(philosophers, dlist_new(phil));
// 		i++;
// 	}
// 	if (fork_init(*philosophers))
// 		return (free_philosophers_and_return(*philosophers));
// 	return (0);
// }

// int	philo_start(t_input input)
// {
// 	t_dlist	*temp;
// 	t_dlist	*philosophers;
// 	t_philo *phil;

// 	philosophers = NULL;
// 	if (philo_init(&philosophers, input))
// 		return (-1);
// 	temp = philosophers;
// 	while (temp)
// 	{
// 		phil = ((t_philo*)temp->content);
// 		phil->timer.last_eaten = get_time();
// 		if (pthread_create(&phil->philosopher, NULL, &philo_create, temp))
// 		{
// 			printf("Create\n");
// 			return (free_philosophers_and_return(philosophers));
// 		}
// 		temp = temp->next;
// 	}
// 	if (philo_join(philosophers))
// 	{
// 		printf("Join\n");
// 		return (free_philosophers_and_return(philosophers));
// 	}
// 	for (temp = philosophers; temp; temp = temp->next)
// 		printf("n eat = %d\n", ((t_philo*)temp->content)->n_eat);
// 	if (fork_destroy(dlist_last(philosophers)))
// 	{
// 		printf("Destroy\n");
// 		return (free_philosophers_and_return(philosophers));
// 	}
// 	phil = ((t_philo*)philosophers->content);
// 	free(phil->dead);
// 	dlist_delete_all(&philosophers, free);
// 	return (0);
// }

// int	free_philosophers_and_return(t_dlist *philosophers)
// {
// 	dlist_delete_all(&philosophers, free);
// 	return (-1);
// }


// static void	fork_assign(t_dlist *philosophers)
// {
// 	t_dlist	*cur;
// 	t_dlist	*next;

// 	cur = philosophers;
// 	while (cur)
// 	{
// 		next = cur->next;
// 		if (next)
// 			((t_philo*)cur->content)->fork_next = &((t_philo*)next->content)->fork;
// 		else
// 			((t_philo*)cur->content)->fork_next = &((t_philo*)philosophers->content)->fork;
// 		cur = next;
// 	}
// }

// int	fork_destroy(t_dlist *philosophers)
// {
// 	t_dlist	*temp;
// 	t_philo	*phil;
	
// 	temp = philosophers;
// 	while (temp->next)
// 	{
// 		phil = ((t_philo*)temp->content);
// 		if (pthread_mutex_destroy(&phil->fork))
// 			return (-1);
// 		temp = temp->next;
// 	}
// 	return (0);
// }

// static int	fork_destroy_part(t_dlist *philosophers)
// {
// 	t_dlist	*temp;
// 	t_philo	*phil;
	
// 	temp = philosophers;
// 	while (temp->prev)
// 	{
// 		phil = ((t_philo*)temp->content);
// 		if (pthread_mutex_destroy(&phil->fork))
// 			return (-1);
// 		temp = temp->prev;
// 	}
// 	return (0);
// }

// int	fork_init(t_dlist *philosophers)
// {
// 	t_dlist	*temp;
// 	t_philo	*phil;

// 	temp = philosophers;
// 	while (temp)
// 	{
// 		phil = ((t_philo*)temp->content);
// 		if (pthread_mutex_init(&phil->fork, NULL))
// 		{
// 			fork_destroy_part(temp);
// 			return (-1);
// 		}
// 		temp = temp->next;
// 	}
// 	fork_assign(philosophers);
// 	return (0);
// }
