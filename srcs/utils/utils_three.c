/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:53:56 by hyap              #+#    #+#             */
/*   Updated: 2022/08/04 22:08:36 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isexpandable(int quo, char *s, char first)
{
	int	condone;
	int	condtwo;

	condone = 0;
	condtwo = 0;
	if (quo == 0 && *s == '$' && (ft_isalpha(*(s + 1)) || *(s + 1) == '?'))
		condone = 1;
	if (*s == first)
		return (condone);
	else if (*(s - 1) != '$')
		condtwo = 1;
	if (condone && condtwo)
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