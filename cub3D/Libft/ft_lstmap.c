/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 01:41:15 by huipark           #+#    #+#             */
/*   Updated: 2022/08/11 18:58:20 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*set(t_list *lst, t_list *newlst
					, void *(*f)(void *), void (*del)(void *))
{
	void	*ptr;
	t_list	*temp;

	while (lst->next)
	{
		lst = lst->next;
		ptr = f(lst->content);
		temp = ft_lstnew(ptr);
		if (!temp)
		{
			del(ptr);
			ft_lstclear(&newlst, del);
			return (0);
		}
		ft_lstadd_back(&newlst, temp);
	}
	return (newlst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	void	*ptr;

	if (!lst)
		return (0);
	ptr = f(lst->content);
	newlst = ft_lstnew(ptr);
	if (!newlst)
	{
		del(ptr);
		return (0);
	}
	newlst = set(lst, newlst, f, del);
	return (newlst);
}
