/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 11:26:38 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/22 17:02:21 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	error_message(char *str)
{
	printf("%s\n", str);
	return (1);
}

static int	no_simulation_just_death(t_input input)
{
	printf("[%.4lu] The philosopher is dead 💀\n", input.max_time_between_meals);
	return (0);
}

static void	initialize_input(t_input *input, int argc, char **argv)
{
	memset(input, UNINITIALIZED, sizeof(*input));
	input->number_of_philosophers = ft_atoi(argv[1]);
	input->max_time_between_meals = ft_atoi(argv[2]);
	input->time_it_takes_to_eat = ft_atoi(argv[3]);
	input->time_it_takes_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input->number_of_meals = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_input	input;

	if (check_arguments(argc, argv))
		return (error_message("Error\nInvalid argument"));
	initialize_input(&input, argc, argv);
	if (check_input(input, argc))
		return (error_message("Error\nInvalid input"));
	if (input.number_of_philosophers == 1)
		return (no_simulation_just_death(input));
	setup_simulation(input);
	return (0);
}
