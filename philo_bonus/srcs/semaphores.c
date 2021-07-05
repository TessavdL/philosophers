/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semaphores.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/22 13:42:50 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/07/05 13:19:41 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	assign_helpers(int number_of_philosphers,
	t_philosopher *philosophers, sem_t **dead_semaphore,
	sem_t **print_semaphore)
{
	int	i;

	i = 0;
	while (i < number_of_philosphers)
	{
		philosophers[i].print_semaphore = *print_semaphore;
		philosophers[i].dead_semaphore = *dead_semaphore;
		i++;
	}
}

void	assign_forks(int number_of_philosphers, t_philosopher *philosophers,
	sem_t **forks)
{
	int	i;

	i = 0;
	while (i < number_of_philosphers)
	{
		philosophers[i].forks = *forks;
		i++;
	}
}

int	unlink_and_open_semaphores(int number_of_philosophers, sem_t **forks,
	sem_t **print_semaphore, sem_t **dead_semaphore)
{
	sem_unlink("forks");
	*forks = sem_open("forks", O_CREAT, 0666, number_of_philosophers);
	if (*forks == SEM_FAILED)
		return (ERROR_FAILED_TO_INITIALIZE_SEMAPHORE);
	sem_unlink("print_semaphore");
	*print_semaphore = sem_open("print_semaphore", O_CREAT, 0666, 1);
	if (*print_semaphore == SEM_FAILED)
		return (ERROR_FAILED_TO_INITIALIZE_SEMAPHORE);
	sem_unlink("dead_semaphore");
	*dead_semaphore = sem_open("dead_semaphore", O_CREAT, 0666, 1);
	if (*dead_semaphore == SEM_FAILED)
		return (ERROR_FAILED_TO_INITIALIZE_SEMAPHORE);
	return (0);
}
