/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 11:12:38 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/24 13:36:47 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

# define UNINITIALIZED 0
# define CHILD 0

// -----------------------------------STRUCTS-----------------------------------

typedef enum e_error
{
	NO_ERROR = 0,
	ERROR_INCORRECT_NUMBER_OF_ARGUMENTS = 1,
	ERROR_ARGUMENT_IS_NOT_NUMERIC = 2,
	ERROR_INVALID_INPUT = 3,
	ERROR_FAILED_TO_INITIALIZE_FORKS = 4,
	ERROR_FAILED_TO_INITIALIZE_SEMAPHORE = 5,
	ERROR_FAILED_TO_FORK_THE_PROCESS = 6,
	ERROR_FAILED_TO_CREATE_THREAD = 7,
	ERROR_FAILED_TO_DETACH_THREAD = 8,
	ERROR_FAILED_TO_LOCK_SEMAPHORE = 9,
	ERROR_FAILED_TO_UNLOCK_SEMAPHORE = 10,
	ERROR_FAILED_TO_KILL_PROCESS = 11,
	ERROR_MALLOC_FAILED = 12,
}	t_error;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1,
}	t_bool;

typedef struct s_input
{
	int				number_of_philosophers;
	int				number_of_meals;
	unsigned long	max_time_between_meals;
	unsigned long	time_it_takes_to_eat;
	unsigned long	time_it_takes_to_sleep;
}	t_input;

typedef struct s_philosopher
{
	char			*name;
	int				id;
	int				number_of_meals_eaten;
	int				total_number_of_meals;
	unsigned long	max_time_between_meals;
	unsigned long	time_it_takes_to_eat;
	unsigned long	time_it_takes_to_sleep;
	unsigned long	time_of_last_meal;
	unsigned long	time_start;
	t_bool			*dead;
	pid_t			philosopher;
	sem_t			*forks;
	sem_t			*print_semaphore;
}	t_philosopher;

// ---------------------------------PROTOTYPES---------------------------------

// void	*checking_for_death

// check_arguments.c
int					check_arguments(int argc, char **argv);

// check_input.c
int					check_input(t_input input, int argc);

// eat_sleep_think.c
void				eat_sleep_think_repeat(t_philosopher *philosopher);

// forks.c
void 				initialize_forks(int number_of_philosophers,
						t_philosopher *philosophers, sem_t **forks,
						sem_t **print_semaphore);

// end_simulation.c

// start_simulation.c
void				setup_simulation(t_input input);

// utils_atoi.c
int					ft_atoi(const char *str);

// utils.c
t_bool				check_if_a_philosopher_is_dead(t_philosopher *phil);
int					ft_isdigit(int c);
unsigned long		get_time(void);
void				print_message(char *message, t_philosopher *philosopher);

#endif
