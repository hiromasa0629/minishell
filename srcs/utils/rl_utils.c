/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 21:58:52 by hyap              #+#    #+#             */
/*   Updated: 2022/09/01 09:31:16 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prompt_new_readline(void)
{
	printf("\n");
	if (g_status.in_cmds == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}	
}

void	prompt_error_readline(void)
{
}

void	ft_add_history(char *s)
{
	if (ft_strlen(s) > 0)
		add_history(s);
	return ;
}
