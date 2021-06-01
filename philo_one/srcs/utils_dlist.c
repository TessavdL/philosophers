/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tevan-de <tevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/28 18:16:03 by tevan-de      #+#    #+#                 */
/*   Updated: 2021/05/31 11:18:56 by tevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	dlist_add_back(t_dlist **list, t_dlist *new)
{
	t_dlist	*last;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	last = dlist_last(*list);
	last->next = new;
	new->prev = last;
}

void	dlist_add_front(t_dlist **list, t_dlist *new)
{
	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	(*list)->prev = new;
	new->next = *list;
	*list = new;
}

void	dlist_delete_all(t_dlist **list, void (*del)(void *))
{
	t_dlist		*cur;
	t_dlist		*next;

	if (!list)
		return ;
	cur = *list;
	while (cur)
	{
		next = cur->next;
		dlist_delete_one(cur, del);
		cur = next;
	}
	*list = NULL;
}

void	dlist_delete_one(t_dlist *list, void (*del)(void *))
{
	if (!list)
		return ;
	del(list->content);
	free(list);
	list = NULL;
}

void	dlist_iter(t_dlist *list, void (*f)(void*))
{
	if (!list)
		return ;
	while (list)
	{
		f(list->content);
		list = list->next;
	}
}

t_dlist	*dlist_last(t_dlist *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

t_dlist	*dlist_new(void *content)
{
	t_dlist	*list;

	list = malloc(sizeof(t_dlist));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

int		dlist_size(t_dlist *list)
{
	int	i;

	if (!list)
		return (0);
	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}
