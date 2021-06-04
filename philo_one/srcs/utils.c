/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 12:17:29 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/03 22:47:40 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

static long int	ft_fkatoi(const char *str, unsigned long int res, int sign)
{
	while (*str && *str >= '0' && *str <= '9')
	{
		if ((res > 922337203685477580 || (res == 922337203685477580
			&& (*str - '0') > 7)) && sign == 1)
			return (-1);
		else if ((res > 922337203685477580 || (res == 922337203685477580
			&& (*str - '0') > 8)) && sign == -1)
			return (0);
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	unsigned long int	res;
	int					sign;

	res = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	res = ft_fkatoi(str, res, sign);
	return (res * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval	tv;
	unsigned long	seconds;
	unsigned long	microseconds;

	gettimeofday(&tv, NULL);
	seconds = tv.tv_sec * 1000;
	microseconds = tv.tv_usec / 1000;
	return (seconds + microseconds);
}

bool	check_dead_timer(t_philo *phil)
{
	long long	time;
	long long	time_between_meals;


	time = (long long)get_time();
	time_between_meals = time - (long long)phil->timer.last_eaten;
	if ((long long)phil->timer.death < time_between_meals)
		return (true);
	return (false);
}

bool	check_if_will_be_dead(t_philo *phil, int eat, int sleep)
{
	long long	time;
	long long	time_between_meals;

	time = (long long)get_time();
	time_between_meals = time - (long long)phil->timer.last_eaten;
	if (eat)
	{
		if (time_between_meals + phil->timer.eat > phil->timer.death)
			return (true);
		else
			return (false);
	}
	if (sleep)
	{
		if (time_between_meals + phil->timer.sleep > phil->timer.death)
			return (true);
		else
			return (false);
	}
	return (false);
}
