/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_arguments.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 11:12:04 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/22 12:59:16 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static t_bool	check_if_string_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (FALSE);
	else
		return (TRUE);
}

static t_bool	check_if_arguments_are_numeric(char **arguments)
{
	int	i;

	i = 1;
	while (arguments[i])
	{
		if (check_if_string_is_numeric(arguments[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	check_if_number_of_arguments_is_valid(int argument_count)
{
	if (argument_count != 5 && argument_count != 6)
		return (FALSE);
	else
		return (TRUE);
}

int	check_arguments(int argument_count, char **arguments)
{
	if (check_if_number_of_arguments_is_valid(argument_count) == FALSE)
		return (ERROR_INCORRECT_NUMBER_OF_ARGUMENTS);
	if (check_if_arguments_are_numeric(arguments) == FALSE)
		return (ERROR_ARGUMENT_IS_NOT_NUMERIC);
	return (NO_ERROR);
}
