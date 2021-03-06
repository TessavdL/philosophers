/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 11:21:31 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/25 13:00:16 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int	check_input(t_input input, int argument_count)
{
	if (input.number_of_philosophers < 1 || input.number_of_philosophers > 200)
		return (ERROR_INVALID_INPUT);
	if (input.max_time_between_meals < 60)
		return (ERROR_INVALID_INPUT);
	if (input.time_it_takes_to_eat < 60)
		return (ERROR_INVALID_INPUT);
	if (input.time_it_takes_to_sleep < 60)
		return (ERROR_INVALID_INPUT);
	if (argument_count == 6 && input.number_of_meals < 1)
		return (ERROR_INVALID_INPUT);
	return (NO_ERROR);
}
