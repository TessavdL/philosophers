/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 11:26:38 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/02 09:48:00 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

// static void	print_input(t_input input)
// {
// 	printf("number of philosophers = %d\n", input.n_philo);
// 	printf("time to die = %d\n", input.t_die);
// 	printf("time to eat = %d\n", input.t_eat);
// 	printf("time to sleep = %d\n", input.t_sleep);
// 	printf("number of times each philosopher must eat = %d\n", input.n_eat);
// }

static void	initialize_input(t_input *input, int argc, char **argv)
{
	memset(input, -2, sizeof(*input));
	input->n_philo = ft_atoi(argv[1]);
	input->timer.death = ft_atoi(argv[2]);
	input->timer.eat = ft_atoi(argv[3]);
	input->timer.sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input->n_eat = ft_atoi(argv[5]);
	input->timer.last_eaten = 0;
}

int	main(int argc, char **argv)
{
	t_input	input;

	if (check_arguments(argc, argv))
	{
		printf("Invalid input\n");
		return (0);
	}
	initialize_input(&input, argc, argv);
	if (check_input(input, argc))
	{
		printf("Invalid input\n");
		return (0);
	}
	// print_input(input);
	if (philo_start(input) == -1)
	{
		printf("An error occured in philo_start\n");
		return (-1);
	}
	return (0);
}
