/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:59:51 by hyap              #+#    #+#             */
/*   Updated: 2022/08/11 14:37:09 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**********************************
 * *s		element->ele
 * 
 * i		iterate element->ele
 * quote	check closing quote
 * len		return value
**********************************/
int	length_without_quotes(char *s)
{
	t_helper	h;
	int			tmp_quote;

	h.i = 0;
	h.quote = 0;
	h.len = 0;
	while (s[h.i])
	{
		if (ft_isquotes(s[h.i]))
		{
			tmp_quote = s[h.i];
			check_in_quotes(s[h.i], &(h.quote));
			if (h.quote != 0 && h.quote != tmp_quote)
				h.len++;
		}
		else
			h.len++;
		h.i++;
	}
	return (h.len);
}

void	store_removed_quotes(char **new_ele, char *s)
{
	t_helper	h;
	int			tmp_quote;

	h.quote = 0;
	h.i = 0;
	h.j = 0;
	while (s[h.i])
	{
		if (ft_isquotes(s[h.i]))
		{
			tmp_quote = s[h.i];
			check_in_quotes(s[h.i], &(h.quote));
			if (h.quote != 0 && h.quote != tmp_quote)
			{
				(*new_ele)[h.j++] = s[h.i++];
				continue ;
			}
		}
		else
			(*new_ele)[h.j++] = s[h.i];
		h.i++;
	}
}

void	remove_quotes(t_element **el)
{
	t_helper	h;

	h.line = (*el)->ele;
	h.len = length_without_quotes(h.line);
	// printf("len: %d\n", h.len + 1);
	h.linetwo = (char *)malloc(sizeof(char) * (h.len + 1));
	h.linetwo[h.len] = '\0';
	store_removed_quotes(&(h.linetwo), h.line);
	free((*el)->ele);
	(*el)->ele = h.linetwo;
}

void	ft_parser(t_data *data)
{
	t_list		*seclst;
	t_list		*ellst;
	t_element	*el;

	seclst = data->seclst;
	while (seclst)
	{
		ellst = ((t_section *)seclst->content)->ellst;
		while (ellst)
		{	
			el = (t_element *)ellst->content;
			if (ft_has_quotes(el->ele))
				remove_quotes(&el);
			ellst = ellst->next;
		}
		// ft_lstiter(((t_section *)seclst->content)->ellst, print_ele_content);
		seclst = seclst->next;
	}
	// printf("%s============================\n", WHITE);
}