/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_section.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:16:42 by hyap              #+#    #+#             */
/*   Updated: 2022/08/03 16:26:46 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	loop_split_isspace(char c, int quote)
{
	if ((c && !ft_isspace(c)) || (c && ft_isspace(c) && quote != 0))
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
	while (loop_split_isspace(s[i], quote))
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
	printf("%sel_len: %d\n", WHITE, el_len + 1);
	s[el_len] = '\0';
	i = 0;
	quote = 0;
	while (loop_split_isspace(**sec, quote))
	{
		if (ft_isquotes(**sec))
			check_in_quotes(**sec, &quote);
		s[i++] = **sec;
		(*sec)++;
	}
	return (s);
}

void	store_element(t_section **section, char **sec)
{
	t_element	*el;

	el = (t_element *)malloc(sizeof(t_element));
	el->ele = create_ele(sec);
	el->parent = (*section)->numth;
	ft_lstadd_back(&(*section)->ellst, ft_lstnew(el));
	(*section)->el_count++;
}

void	split_section(t_section **section)
{
	char	*sec;

	sec = (*section)->sec;
	(*section)->el_count = 1;
	while (*sec)
	{
		while (ft_isspace(*sec))
			sec++;
		store_element(section, &sec);
		while (ft_isspace(*sec))
			sec++;
	}
}