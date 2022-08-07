/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 21:20:09 by hyap              #+#    #+#             */
/*   Updated: 2022/08/05 12:58:05 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Get strncmp 'n' while moving *env_var */
int	get_strncmp_n(char *env_var, int *i)
{
	int	n;

	n = 0;
	while (ft_isalpha(env_var[*i]) || ft_isnum(env_var[*i]))
	{
		(*i)++;
		n++;
	}
	return (n);
}