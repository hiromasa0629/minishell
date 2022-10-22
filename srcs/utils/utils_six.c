/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_six.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:23:28 by hyap              #+#    #+#             */
/*   Updated: 2022/10/22 14:28:05 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_has_special_export(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalpha(s[i]) && !ft_isnum(s[i]) && s[i] != '=' && s[i] != '_')
			return (1);
		if (s[i] == '=')
			count++;
		i++;
	}
	if (count > 1)
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
