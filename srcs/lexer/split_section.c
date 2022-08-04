/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_section.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:16:42 by hyap              #+#    #+#             */
/*   Updated: 2022/08/04 19:16:34 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	loop_split_isspace_isredirectop(char c, int quote)
{
	int	cond_one;
	int	cond_two;

	cond_one = 0;
	cond_two = 0;
	if ((c && !ft_isspace(c)) || (c && ft_isspace(c) && quote != 0))
		cond_one = 1;
	if ((c && !ft_isredirectop(c)) || (c && ft_isredirectop(c) && quote != 0))
		cond_two = 1;
	if (cond_one && cond_two)
		return (1);
	return (0);
}

int	element_len(char *s)
{
	int	i;
	int	count;
	int	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (ft_isspace(s[i]))
		i++;
	while (loop_split_isspace_isredirectop(s[i], quote))
	{
		if (ft_isquotes(s[i]))
			check_in_quotes(s[i], &quote);
		count++;
		i++;
	}
	return (count);
}

char	*create_ele(char **sec)
{
	char	*s;
	int		el_len;
	int		i;
	int		quote;

	el_len = element_len(*sec);
	s = (char *)malloc(sizeof(char) * (el_len + 1));
	// printf("%sel_len: %d\n", WHITE, el_len + 1);
	s[el_len] = '\0';
	i = 0;
	quote = 0;
	while (loop_split_isspace_isredirectop(**sec, quote))
	{
		if (ft_isquotes(**sec))
			check_in_quotes(**sec, &quote);
		s[i++] = **sec;
		(*sec)++;
	}
	return (s);
}

void	store_element(t_section **section, char **sec, char *op)
{
	t_element	*el;

	while (ft_isspace(**sec))
		(*sec)++;
	el = (t_element *)malloc(sizeof(t_element));
	el->numth = (*section)->el_count - 1;
	if (!op)
		el->ele = create_ele(sec);
	else
		el->ele = op;
	el->parent = (*section)->numth;
	el->is_good = 1;
	ft_lstadd_back(&(*section)->ellst, ft_lstnew(el));
	(*section)->el_count++;
	while (ft_isspace(**sec))
		(*sec)++;
}

void	split_section(t_section **section)
{
	char	*sec;
	char	*op;
	int		op_count;

	sec = (*section)->sec;
	(*section)->el_count = 1;
	while (*sec)
	{
		if (ft_isredirectop(*sec))
		{
			if (*sec == *(sec + 1))
				op_count = 2;
			else
				op_count = 1;
			op = (char *)malloc(sizeof(char) * (op_count + 1));
			op[op_count] = '\0';
			while (op_count--)
				op[op_count] = *(sec)++;
			store_element(section, &sec, op);
		}
		else
			store_element(section, &sec, NULL);
	}
}
