/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 11:12:38 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/22 12:29:55 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define UNINITIALIZED 0

// -----------------------------------STRUCTS-----------------------------------

typedef enum e_error
{
	NO_ERROR = 0,
	ERROR_INCORRECT_NUMBER_OF_ARGUMENTS = -1,
	ERROR_ARGUMENT_IS_NOT_NUMERIC = -2,
	ERROR_INVALID_INPUT = -3,
	ERROR_FAILED_TO_CREATE_THREAD = -4,
	ERROR_FAILED_TO_INITIALIZE_FORKS = -5,
	ERROR_FAILED_TO_JOIN_THREADS = -6,
	ERROR_FAILED_TO_DESTROY_FORKS = -7,
	ERROR_FAILED_TO_INITIALIZE_PRINT_MUTEX = -8,
	ERROR_MALLOC_FAILED = -9,
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
	pthread_t		philosopher;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*print_mutex;
}	t_philosopher;

// ---------------------------------PROTOTYPES---------------------------------

// check_arguments.c
int					check_arguments(int argc, char **argv);

// check_input.c
int					check_input(t_input input, int argc);

// eat_sleep_think.c
void				eat_sleep_think(t_philosopher *phil);
void				*eat_sleep_think_repeat(void *philosopher);

// end_simulation.c
int					end_simulation(t_philosopher *philosophers,
						int number_of_philosophers);

// fork.c
int					destroy_forks(t_philosopher *philosophers, int n_philo);
int					initiliaze_forks(t_philosopher *philosophers, int n_philo);

// start_simulation.c
int					setup_simulation(t_input input);

// utils_atoi.c
int					ft_atoi(const char *str);

// utils.c
t_bool				check_if_a_philosopher_is_dead(t_philosopher *phil);
int					ft_isdigit(int c);
unsigned long		get_time(void);
void				print_message(char *message, t_philosopher *philosopher);

#endif
