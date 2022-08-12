/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 21:58:52 by hyap              #+#    #+#             */
/*   Updated: 2022/08/12 12:09:54 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prompt_new_readline(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	prompt_error_readline(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	ft_add_history(char *s)
{
	if (ft_strlen(s) > 0)
		add_history(s);
	return ;
}
