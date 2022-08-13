/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_six.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:23:28 by hyap              #+#    #+#             */
/*   Updated: 2022/08/13 09:27:44 by hyap             ###   ########.fr       */
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
