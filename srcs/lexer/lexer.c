/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:51:39 by hyap              #+#    #+#             */
/*   Updated: 2022/08/07 20:45:25 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/************************************
 * i			traversing index
 * line			(*el)->ele
 * linetwo		tmp moving pointer of (*el)->ele
 * linethree	new ele
*************************************/
void	split_absolute(t_element **el)
{
	t_helper	h;

	h.i = 0;
	h.line = (*el)->ele;
	h.linetwo = NULL;
	while ((h.line)[h.i])
	{
		if ((h.line)[h.i] == '/')
			h.linetwo = &(h.line)[h.i + 1];
		h.i++;
	}
	h.linethree = (char *)malloc(sizeof(char) * (ft_strlen(h.linetwo) + 1));
	h.linethree[ft_strlen(h.linetwo)] = '\0';
	h.i = 0;
	while (*(h.linetwo))
		h.linethree[h.i++] = *(h.linetwo)++;
	free((*el)->ele);
	(*el)->ele = h.linethree;
}

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
		if (element->type == TYPE_CMD && ft_hasslash(element->ele))
			split_absolute(&element);
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

void	ft_lexer(t_data *data, char *line, char **envp)
{
	t_list		*seclst;
	t_section	*section;

	printf("%s============================\n", WHITE);
	split_pipe(data, line);
	// printf("%s, %d\n", ((t_section *)data->seclst->content)->sec, data->sec_count);
	ft_lstiter(data->seclst, print_sec_content);
	printf("%s----------------------------\n", WHITE);
	seclst = data->seclst;
	while (seclst)
	{
		section = (t_section *)seclst->content;
		split_section(&section);
		expand_section(&section, envp);
		skip_empty_ele(&section);
		assign_numth(&section);
		ft_lstiter(((t_section *)seclst->content)->ellst, print_ele_content);
		printf("%s----------------------------\n", WHITE);
		complete_element(&section);
		ft_lstiter(((t_section *)seclst->content)->ellst, print_ele_content);
		seclst = seclst->next;
		printf("%s----------------------------\n", WHITE);
	}
	printf("%s============================\n", WHITE);
}
