/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:39:10 by hyap              #+#    #+#             */
/*   Updated: 2022/09/05 14:15:30 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_restore_sigint(int signum)
{
	(void)signum;
	ft_putstr_fd(1, "\n");
	return ;
}

void	handle_restore_sigqiut(int signum)
{
	(void)signum;
	ft_putstr_fd(1, "Quit: 3\n");
	g_status = 131;
	return ;
}

void	restore_signal(void)
{
	signal(SIGINT, handle_restore_sigint);
	signal(SIGQUIT, handle_restore_sigqiut);
}

void	ft_executor(t_data *data)
{
	t_list		*seclst;
	t_list		*ellst;

	seclst = data->seclst;
	data->pipein = -1;
	data->pipeout = -1;
	data->tmpstdin = -1;
	data->tmpstdout = -1;
	restore_signal();
	if (data->sec_count > 1)
	{
		while (seclst)
		{
			ellst = ((t_section *)seclst->content)->ellst;
			multiple_sections(ellst, data, seclst);
			seclst = seclst->next;
		}
	}
	else
		single_section(((t_section *)seclst->content)->ellst, data);
	while (waitpid(-1, &(g_status), 0) > 0)
		;
	g_status = WEXITSTATUS(g_status);
}
