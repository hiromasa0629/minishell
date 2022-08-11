/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:42:20 by hyap              #+#    #+#             */
/*   Updated: 2022/08/11 16:02:23 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_redirectop(char *s, int *i, int quote)
{
	if (ft_isredirectop(s[*i]) && ft_isredirectop(s[*i + 1]) && quote == 0)
	{
		if (s[*i] != s[*i + 1])
			return (0);
		(*i)++;
		if (ft_isredirectop(s[*i + 1]))
			return (0);
	}
	return (1);
}

void	print_err(char *s, void (*prompt)(void))
{
	ft_putstr_fd(2, s);
	prompt();
}

char	*error_msg(int err_code)
{
	if (err_code == PIPES_ERR)
		return ("Pipes error\n");
	if (err_code == QUOTES_ERR)
		return ("Quotes error\n");
	if (err_code == SCHAR_ERR)
		return ("Special character error\n");
	if (err_code == OP_ERR)
		return ("Redirect operator error\n");
	return (NULL);
}
