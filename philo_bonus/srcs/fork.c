/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/22 13:42:50 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/24 11:29:31 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	assign_forks(int number_of_philosphers, t_philosopher *philosophers,
	sem_t **forks, sem_t **print_semaphore)
{
	int	i;

	i = 0;
	while (i < number_of_philosphers)
	{
		philosophers[i].forks = *forks;
		philosophers[i].print_semaphore = *print_semaphore;
		i++;
	}
}

static int	initialize_semaphores(int number_of_philosophers, sem_t **forks,
	sem_t **print_semaphore)
{
	sem_unlink("forks");
	*forks = sem_open("forks", O_CREAT, 0666, number_of_philosophers);
	if (*forks == SEM_FAILED)
		return (ERROR_FAILED_TO_INITIALIZE_SEMAPHORE);
	sem_unlink("print_semaphore");
	*print_semaphore = sem_open("print_semaphore", O_CREAT, 0644, 1);
	if (*print_semaphore == SEM_FAILED)
		return (ERROR_FAILED_TO_INITIALIZE_SEMAPHORE);
	return (0);
}

void initialize_forks(int number_of_philosophers, t_philosopher *philosophers,
	sem_t **forks, sem_t **print_semaphore)
{
	if (initialize_semaphores(number_of_philosophers, forks, print_semaphore))
		exit(ERROR_FAILED_TO_INITIALIZE_SEMAPHORE);
	assign_forks(number_of_philosophers, philosophers, forks, print_semaphore);
}
