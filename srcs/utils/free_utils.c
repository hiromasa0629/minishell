/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 21:44:44 by hyap              #+#    #+#             */
/*   Updated: 2022/08/04 16:31:22 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	del_el(void *content)
{
	t_element	*ele;

	ele = (t_element *)content;
	free(ele->ele);
	free(ele);
}

void	del_sec(void *content)
{
	t_section	*sec;

	sec = (t_section *)content;
	free(sec->sec);
	free(sec);
}

void	free_all(t_data *data)
{
	t_list	*ellst;

	while (data->seclst)
	{
		ellst = ((t_section *)data->seclst->content)->ellst;
		data->seclst = data->seclst->next;
		ft_lstclear(&ellst, del_el);
	}
	ft_lstclear(&data->seclst, del_sec);
}