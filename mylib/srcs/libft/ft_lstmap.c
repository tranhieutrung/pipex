/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:24:57 by hitran            #+#    #+#             */
/*   Updated: 2024/06/07 09:42:10 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_rest;
	t_list	*node_res;
	void	*set;

	if (!lst || !f || !del)
		return (NULL);
	lst_rest = NULL;
	while (lst)
	{
		set = f(lst->content);
		node_res = ft_lstnew(set);
		if (!node_res)
		{
			del(set);
			ft_lstclear(&lst_rest, (*del));
			return (lst_rest);
		}
		ft_lstadd_back(&lst_rest, node_res);
		lst = lst->next;
	}
	return (lst_rest);
}
