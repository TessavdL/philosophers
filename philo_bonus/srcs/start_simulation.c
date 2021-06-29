/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_simulation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/22 12:59:06 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/24 13:36:54 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include "../includes/names.h"

static void wait_for_simulation_to_terminate(t_philosopher *philosophers,
	int number_of_philosophers)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < number_of_philosophers)
	{
		waitpid(philosophers[i].philosopher, &wstatus, 0);
		i++;
	}
}

static void	start_simulation(int number_of_philosophers,
	t_philosopher *philosophers)
{
	int		i;

	i = 0;
	while (i < number_of_philosophers)
	{
		philosophers[i].time_start = get_time();
		philosophers[i].time_of_last_meal = philosophers[i].time_start;
		philosophers[i].philosopher = fork();
		if (philosophers[i].philosopher == -1)
			exit(ERROR_FAILED_TO_FORK_THE_PROCESS);
		else if (philosophers[i].philosopher == CHILD)
			eat_sleep_think_repeat(&philosophers[i]);
		i++;
	}
 	wait_for_simulation_to_terminate(philosophers, number_of_philosophers);
}

static void	initialize_philosopher(int i, t_bool *dead, t_input input,
	t_philosopher *philosopher)
{
	memset(philosopher, 0, sizeof(*philosopher));
	philosopher->name = (char *)names[i];
	philosopher->id = i + 1;
	philosopher->total_number_of_meals = input.number_of_meals;
	philosopher->max_time_between_meals = input.max_time_between_meals;
	philosopher->time_it_takes_to_eat = input.time_it_takes_to_eat;
	philosopher->time_it_takes_to_sleep = input.time_it_takes_to_sleep;
	philosopher->dead = dead;
}

static t_philosopher	*initialize_philosophers(t_bool *dead, t_input input)
{
	int				i;
	t_philosopher	*philosophers;

	philosophers = malloc(sizeof(t_philosopher) * input.number_of_philosophers);
	if (!philosophers)
		exit(ERROR_MALLOC_FAILED);
	i = 0;
	while (i < input.number_of_philosophers)
	{
		initialize_philosopher(i, dead, input, &philosophers[i]);
		i++;
	}
	return (philosophers);
}

void	setup_simulation(t_input input)
{
	// pthread_t		death_check;
	t_bool			dead;
	t_philosopher	*philosophers;
	sem_t			*forks;
	sem_t			*print_semaphore;

	dead = FALSE;
	philosophers = initialize_philosophers(&dead, input);
	initialize_forks(input.number_of_philosophers, philosophers, &forks, &print_semaphore);
	// pthread_create(&death_check, NULL, &checking_for_dead, &philosophers);
	// pthread_detach(death_check);
	start_simulation(input.number_of_philosophers, philosophers);
	sem_unlink("forks");
	sem_unlink("print_semaphore");
	sem_close(forks);
	sem_close(print_semaphore);
	free(philosophers);
	exit(0);
}
