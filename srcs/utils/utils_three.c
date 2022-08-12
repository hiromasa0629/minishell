/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:53:56 by hyap              #+#    #+#             */
/*   Updated: 2022/08/12 12:15:52 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isexpandable(int quo, char *s, int i)
{
	int	condone;
	int	condtwo;

	condone = 0;
	condtwo = 0;
	if ((quo == 0 || quo == '\"') && s[i] == '$' && (ft_isalpha(s[i + 1]) || \
		s[i + 1] == '?'))
		condone = 1;
	if (i == 0)
		return (condone);
	if (s[i - 1] != '$')
		condtwo = 1;
	if (condone && condtwo)
		return (1);
	return (0);
}

int	ft_has_quotes(char *s)
{
	while (*s)
		if (ft_isquotes(*(s)++))
			return (1);
	return (0);
}

int	ft_has_envvar(char *s)
{
	while (*s)
		if (*(s)++ == '$')
			return (1);
	return (0);
}

int	ft_iscomplete_op(char *s)
{
	if (ft_strncmp(s, ">", 1) == 0)
		return (1);
	if (ft_strncmp(s, "<", 1) == 0)
		return (1);
	if (ft_strncmp(s, ">>", 2) == 0)
		return (1);
	if (ft_strncmp(s, "<<", 2) == 0)
		return (1);
	return (0);
}

int	ft_hasslash(char *s)
{
	while (*s)
		if (*(s)++ == '/')
			return (1);
	return (0);
}
