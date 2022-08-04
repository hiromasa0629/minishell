/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:07:28 by hyap              #+#    #+#             */
/*   Updated: 2022/08/04 16:28:42 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isfile(t_list *ellst)
{
	int	condone;
	int	condtwo;

	condone = 0;
	condtwo = 0;
	if (!ellst->prev)
		return (0);
	if (((t_element *)ellst->prev->content)->type == TYPE_REDIRECT)
		condone = 1;
	if (ft_strncmp(((t_element *)ellst->prev->content)->ele, "<<", 2) != 0)
		condtwo = 1;
	if (condone && condtwo)
		return (1);
	return (0);
}

int	ft_iscommand(t_list *ellst)
{
	t_list		*tmp;
	t_element	*el;
	t_element	*prev_el;

	tmp = ellst;
	el = (t_element *)ellst->content;
	while (tmp->prev)
		tmp = tmp->prev;
	if (((t_element *)tmp->content)->type == TYPE_REDIRECT)
	{
		prev_el = (t_element *)ellst->prev->content;
		if (prev_el->type == TYPE_FILE)
			return (1);
		if (prev_el->type == TYPE_DELIMITER)
			return (1);
	}
	else if (el->numth == 0 && !ft_isredirectop((el->ele)[0]))
		return (1);
	return (0);
}

int	ft_isflag(t_list *ellst)
{
	char	*ele;

	if (!ellst->prev)
		return (0);
	ele = ((t_element *)ellst->content)->ele;
	if (((t_element *)ellst->prev->content)->type == TYPE_CMD && ele[0] == '-')
		return (1);
	return (0);
}

int	ft_isdelimiter(t_list *ellst)
{
	if (!ellst->prev)
		return (0);
	if (ft_strncmp(((t_element *)ellst->prev->content)->ele, "<<", 2) == 0)
		return (1);
	return (0);
}

void	complete_element(t_section **section)
{
	t_list		*ellst;
	t_element	*element;

	ellst = (*section)->ellst;
	while (ellst)
	{
		element = (t_element *)ellst->content;
		if (ft_iscommand(ellst))
			element->type = TYPE_CMD;
		else if (ft_isredirectop((element->ele)[0]))
			element->type = TYPE_REDIRECT;
		else if (ft_isfile(ellst))
			element->type = TYPE_FILE;
		else if (ft_isdelimiter(ellst))
			element->type = TYPE_DELIMITER;
		else if (ft_isflag(ellst))
			element->type = TYPE_FLAG;
		else
			element->type = TYPE_ARG;
		ellst = ellst->next;
	}
}
