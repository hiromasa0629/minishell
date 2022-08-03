/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:07:28 by hyap              #+#    #+#             */
/*   Updated: 2022/08/03 17:48:14 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	loop_split_redirectop(char c, int quote)
{
	if (c && !ft_isredirectop(c) || (c && ft_isredirectop(c) && quote != 0))
		return (1);
	return (0);
}

void	insert_new_el(t_list **ellst, char *new_el)
{
	t_element	*redirectop_el;
	t_list		*tmp;

	redirectop_el = (t_element *)malloc(sizeof(t_element));
	redirectop_el->ele = new_el;
	tmp = (*ellst)->next;
	(*ellst)->next = ft_lstnew(redirectop_el);
	tmp->prev = (*ellst)->next;
	(*ellst)->next->next = tmp;
	*ellst = (*ellst)->next;
}

int	new_ele_length(char	*ele)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (loop_split_redirectop(ele[i], quote))
	{
		if (ft_isquotes(ele[i]))
			check_in_quotes(ele[i], &quote);
		i++;
	}
	return (i);
}

void	store_new_el(t_list **ellst, char **ele)
{
	int		ele_len;
	int		quote;
	int		i;
	char	*s;

	ele_len = new_ele_length(*ele);
	quote = 0;
	i = 0;
	s = (char *)malloc(sizeof(char) * (ele_len + 1));
	s[ele_len] = '\0';
	while (loop_split_redirectop(**ele, quote))
	{
		if (ft_isquotes(**ele))
			check_in_quotes(**ele, &quote);
		s[i++] = **ele;
		(*ele)++;
	}
	((t_element *)(*ellst)->content)->ele = s;
}

void	store_redirectop(t_list **ellst, char **ele)
{
	t_element	*redirectop_el;
	t_list		*tmp;
	char		*new_el;
	int			i;

	i = 0;
	while (*ele[i] && ft_isredirectop(*ele[i]))
		i++;
	new_el = (char *)malloc(sizeof(char) * (i) + 1);
	new_el[count] = '\0';
	while (**ele && ft_isredirectop(**ele))
	{
		new_el[i++] = **ele;
		(*ele)++;
	}
	insert_new_el(ellst, new_el);
}

void	split_element(t_list **ellst)
{
	char		*ele;
	int			i;
	int			quote;
	t_element	*el;

	while (*ellst)
	{
		ele = ((t_element *)(*ellst)->content)->ele;
		if (!has_redirectop(ele))
			continue ;
		while (*ele)
		{
			if (ft_isredirectop(*ele))
				store_redirectop(ellst, &ele);
			store_new_el(ellst, &ele);
		}
		*ellst = (*ellst)->next;
	}
}

/* assign type to each ele and
and split operators and string */
void	beautify_element(t_section **section)
{
	t_list		*ellst;

	ellst = (*section)->ellst;
	while (ellst)
	{
		split_element(&ellst);
		ellst = ellst->next;
	}
}