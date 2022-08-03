/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:39:29 by hyap              #+#    #+#             */
/*   Updated: 2022/08/03 09:53:50 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_sec_content(void *content)
{
	t_section *sec;

	sec = (t_section *)content;
	printf("%ssec[%d]: %s\n", BLUE, sec->numth, sec->sec);
}

void	print_ele_content(void *content)
{
	t_element *ele;

	ele = (t_element *)content;
	printf("%ssec[%d]ele[%d]: %s\n", GREEN, ele->parent, ele->numth, ele->ele);
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp;

	tmp = lst;
	if (!lst)
		return ;
	while (tmp)
	{
		f(tmp->content);
		tmp = tmp->next;
	}
}