/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/25 17:39:04 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/31 11:37:55 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

static void	fork_assign(t_dlist *philosophers)
{
	// int		i;
	t_dlist	*cur;
	t_dlist	*next;

	cur = philosophers;
	// i = 0;
	while (cur)
	{
		next = cur->next;
		if (next)
		{
			// printf("if i = %d\n", i);
			((t_philo*)cur->content)->fork_next = &((t_philo*)next->content)->fork;
		}
		else
		{
			// printf("else i = %d\n", i);
			((t_philo*)cur->content)->fork_next = &((t_philo*)philosophers->content)->fork;
		}
		cur = next;
		// i++;
	}
}

int	fork_destroy(t_dlist *philosophers)
{
	t_dlist	*temp;
	t_philo	*phil;
	
	temp = philosophers;
	while (temp->next)
	{
		phil = ((t_philo*)temp->content);
		if (pthread_mutex_destroy(&phil->fork))
			return (-1);
		temp = temp->next;
	}
	return (0);
}

static int	fork_destroy_part(t_dlist *philosophers)
{
	t_dlist	*temp;
	t_philo	*phil;
	
	temp = philosophers;
	while (temp->prev)
	{
		phil = ((t_philo*)temp->content);
		if (pthread_mutex_destroy(&phil->fork))
			return (-1);
		temp = temp->prev;
	}
	return (0);
}

int	fork_init(t_dlist *philosophers)
{
	t_dlist	*temp;
	t_philo	*phil;

	temp = philosophers;
	while (temp)
	{
		phil = ((t_philo*)temp->content);
		if (pthread_mutex_init(&phil->fork, NULL))
		{
			fork_destroy_part(temp);
			return (-1);
		}
		temp = temp->next;
	}
	fork_assign(philosophers);
	return (0);
}
