/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_atoi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/17 11:31:58 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/21 12:27:08 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

static long int	calculate_number(const char *str, int sign)
{
	int					i;
	unsigned long int	number;

	i = 0;
	number = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		if ((number > 922337203685477580 || (number == 922337203685477580
					&& (str[i] - '0') > 7)) && sign == 1)
			return (-1);
		else if ((number > 922337203685477580 || (number == 922337203685477580
					&& (str[i] - '0') > 8)) && sign == -1)
			return (0);
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number * sign);
}

static void	skip_whitespaces(const char **str)
{
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
}

int	ft_atoi(const char *str)
{
	int	sign;

	sign = 1;
	skip_whitespaces(&str);
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (calculate_number(str, sign));
}
