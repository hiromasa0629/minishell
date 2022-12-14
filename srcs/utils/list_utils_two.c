/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:39:29 by hyap              #+#    #+#             */
/*   Updated: 2022/08/26 20:10:03 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_sec_content(void *content)
{
	t_section	*sec;

	sec = (t_section *)content;
	dprintf(2, "%ssec[%d]: %s %s\n", BLUE, sec->numth, sec->sec, WHITE);
}

void	print_ele_content(void *content)
{
	t_element	*ele;
	char		*type;

	ele = (t_element *)content;
	type = NULL;
	if (ele->type == TYPE_CMD)
		type = "CMD";
	else if (ele->type == TYPE_FLAG)
		type = "FLAG";
	else if (ele->type == TYPE_ARG)
		type = "ARG";
	else if (ele->type == TYPE_REDIRECT)
		type = "REDIRECT";
	else if (ele->type == TYPE_FILE)
		type = "FILE";
	else if (ele->type == TYPE_DELIMITER)
		type = "DELIMITER";
	else if (ele->type == TYPE_EMPTY)
		type = "EMPTY";
	dprintf(2, "%ssec[%d]ele[%d]: %s, type: %s %s\n", GREEN, ele->parent, \
		ele->numth, ele->ele, type, WHITE);
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
