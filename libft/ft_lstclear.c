/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:18:41 by bbouarab          #+#    #+#             */
/*   Updated: 2025/11/13 10:55:30 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*real_temp;

	if (!lst || !(*lst) || !del)
		return ;
	temp = *lst;
	while (temp->next != NULL)
	{
		real_temp = temp->next;
		del(temp->content);
		free(temp);
		temp = real_temp;
	}
	del(temp->content);
	free(temp);
	*lst = NULL;
}
