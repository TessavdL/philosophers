/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 11:12:38 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/03 22:47:51 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

/*
** STRUCTS
*/

typedef struct		s_timer
{
	unsigned long	death;
	unsigned long	eat;
	unsigned long	last_eaten;
	unsigned long	sleep;
}					t_timer;

typedef struct		s_input
{
	int				n_philo;
	int				n_eat;
	t_timer			timer;
}					t_input;

typedef struct		s_philo
{
	int				i;
	int				n_eat;
	int				total_eat;
	bool			*dead;
	pthread_t		philosopher;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_next;
	t_timer			timer;
}					t_philo;

/*
** PROTOTYPES
*/

/*
** eat_sleep_think.c
*/
void				eat_sleep_think(t_philo *phil);
void				*eat_sleep_think_repeat(void *philosopher);

/*
** fork.c
*/
int					fork_destroy(t_philo *philosophers, int n_philo);
int					fork_init(t_philo *philosophers, int n_philo);

/*
** input.c
*/
int					check_arguments(int argc, char **argv);
int					check_input(t_input input, int argc);

/*
** philo_start.c
*/
int					philo_start(t_input input);

/*
** utlis.c
*/
bool				check_dead_timer(t_philo *phil);
bool				check_if_will_be_dead(t_philo *phil, int eat, int sleep);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
unsigned long		get_time(void);

/*
** utils_dlist.c
*/
// void				dlist_add_back(t_dlist **list, t_dlist *new);
// void				dlist_add_front(t_dlist **list, t_dlist *new);
// void				dlist_delete_all(t_dlist **list, void (*del)(void *));
// void				dlist_delete_one(t_dlist *list, void (*del)(void *));
// void				dlist_iter(t_dlist *list, void (*f)(void*));
// t_dlist				*dlist_last(t_dlist *list);
// t_dlist				*dlist_new(void *content);
// int					dlist_size(t_dlist *list);

#endif
