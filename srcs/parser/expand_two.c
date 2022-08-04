/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 21:20:09 by hyap              #+#    #+#             */
/*   Updated: 2022/08/04 21:23:59 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Get strncmp 'n' while moving *env_var */
int	get_strncmp_n(char **env_var)
{
	int	n;

	n = 0;
	while (ft_isalpha(**env_var) || ft_isnum(**env_var))
	{
		(*env_var)++;
		n++;
	}
	return (n);
}