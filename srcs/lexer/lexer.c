/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:51:39 by hyap              #+#    #+#             */
/*   Updated: 2022/11/10 12:26:44 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	complete_element(t_section **section)
{
	t_list		*ellst;
	t_element	*element;
	t_list		*tmp;

	ellst = (*section)->ellst;
	tmp = ellst;
	tmp = tmp->next;
	while (ellst)
	{
		element = (t_element *)ellst->content;
		assign_types(ellst, &element);
		ellst = ellst->next;
	}
}

void	assign_numth(t_section **section)
{
	t_list		*ellst;
	t_helper	h;

	ellst = (*section)->ellst;
	h.i = 0;
	while (ellst)
	{
		((t_element *)ellst->content)->numth = (h.i)++;
		ellst = ellst->next;
	}
}

void	skip_empty_ele(t_section **section)
{
	t_list	*ellst;
	t_list	*tmp;
	char	*ele;

	ellst = (*section)->ellst;
	ele = ((t_element *)ellst->content)->ele;
	if (!ele[0] && ellst->next)
	{
		tmp = (*section)->ellst;
		(*section)->ellst = (*section)->ellst->next;
		(*section)->ellst->prev = NULL;
		ft_lstdelone(tmp, del_el);
	}
}

/*
** line = readline's line
*/
void	ft_lexer(t_data *data, char *line, char **envp)
{
	t_list		*seclst;
	t_section	*section;

	split_pipe(data, line);
	seclst = data->seclst;
	while (seclst)
	{
		section = (t_section *)seclst->content;
		split_section(&section);
		expand_section(&section, envp);
		skip_empty_ele(&section);
		assign_numth(&section);
		complete_element(&section);
		seclst = seclst->next;
	}
}
