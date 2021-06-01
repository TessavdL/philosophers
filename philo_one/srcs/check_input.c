/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 11:21:31 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/01 11:44:10 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int	check_input(t_input input, int argc)
{
	if (input.n_philo < 1)
		return (1);
	if (input.timer.death < 1)
		return (1);
	if (input.timer.eat < 1)
		return (1);
	if (input.timer.sleep < 1)
		return (1);
	if (argc == 6 && input.n_eat < 1)
		return (1);
	return (0);
}

int	check_arguments(int argc, char **argv)
{
	int		i;
	int		j;
	
	if (argc != 5 && argc != 6)
		return (1);
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j] && ft_isdigit(argv[i][j]))
			j++;
		if (argv[i][j] != '\0')
		{
			printf("Not all digits\n");
			return (1);
		}
		i++;
	}
	return (0);
}