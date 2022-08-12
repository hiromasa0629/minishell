/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:07:28 by hyap              #+#    #+#             */
/*   Updated: 2022/08/12 11:59:23 by hyap             ###   ########.fr       */
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
	t_element	*el;
	t_element	*prev_el;

	el = (t_element *)ellst->content;
	if (ft_has_prev_cmd(ellst))
		return (0);
	if (el->numth > 1 && !ft_isredirectop((el->ele)[0]))
	{
		if (((t_element *)ellst->prev->prev->content)->type == TYPE_REDIRECT)
		{
			prev_el = (t_element *)ellst->prev->content;
			if (prev_el->type == TYPE_FILE)
				return (1);
			if (prev_el->type == TYPE_DELIMITER)
				return (1);
		}
	}
	else if (el->numth == 0 && !ft_isredirectop((el->ele)[0]) && (el->ele)[0])
		return (1);
	return (0);
}

int	ft_isflag(t_list *ellst)
{
	t_element	*el;
	t_element	*p_el;
	int			i;
	int			count;

	if (!ellst->prev)
		return (0);
	el = (t_element *)ellst->content;
	p_el = (t_element *)ellst->prev->content;
	i = 0;
	count = 0;
	while ((el->ele)[i])
		if ((el->ele)[i++] == '-')
			count++;
	if (count > 1)
		return (0);
	if (ft_has_prev_cmd(ellst) && !ft_has_prev_arg(ellst) && \
		(el->ele)[0] == '-')
		return (1);
	if (p_el->type == TYPE_CMD && (el->ele)[0] == '-')
		return (1);
	if (p_el->type == TYPE_CMD && ft_isquotes((el->ele)[0]) && \
		(el->ele)[1] == '-')
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

void	assign_types(t_list *ellst, t_element **el)
{
	if (ft_iscommand(ellst))
		(*el)->type = TYPE_CMD;
	else if ((*el)->is_expanded && ft_isredirectop(((*el)->ele)[0]))
		(*el)->type = TYPE_CMD;
	else if (ft_isredirectop(((*el)->ele)[0]))
	{
		(*el)->type = TYPE_REDIRECT;
		assign_redirect_type(el);
	}
	else if (ft_isfile(ellst))
		(*el)->type = TYPE_FILE;
	else if (ft_isdelimiter(ellst))
		(*el)->type = TYPE_DELIMITER;
	else if (ft_isflag(ellst))
		(*el)->type = TYPE_FLAG;
	else if (!(((*el)->ele)[0]))
		(*el)->type = TYPE_EMPTY;
	else
		(*el)->type = TYPE_ARG;
}
