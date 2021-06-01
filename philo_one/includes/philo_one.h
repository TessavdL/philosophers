/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 11:12:38 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/06/01 12:57:35 by tevan-de      ########   odam.nl         */
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

typedef struct		s_dlist
{
	void			*content;
	void			*next;
	void			*prev;
}					t_dlist;

typedef struct		s_timer
{
	unsigned long	death;
	unsigned long	eat;
	unsigned long	sleep;
	unsigned long	start;
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
	int				total_philo;
	bool			dead;
	pthread_t		philosopher;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_next;
	t_timer			*timer;
}					t_philo;

/*
** PROTOTYPES
*/

/*
** eat_sleep_think.c
*/
void	eat_sleep_think(t_philo *phil);

/*
** fork.c
*/
int					fork_init(t_dlist *philosophers);
int					fork_destroy(t_dlist *philosophers);

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
int					free_philosophers_and_return(t_dlist *philosophers);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
unsigned long		get_time(void);

/*
** utils_dlist.c
*/
void				dlist_add_back(t_dlist **list, t_dlist *new);
void				dlist_add_front(t_dlist **list, t_dlist *new);
void				dlist_delete_all(t_dlist **list, void (*del)(void *));
void				dlist_delete_one(t_dlist *list, void (*del)(void *));
void				dlist_iter(t_dlist *list, void (*f)(void*));
t_dlist				*dlist_last(t_dlist *list);
t_dlist				*dlist_new(void *content);
int					dlist_size(t_dlist *list);

#endif
