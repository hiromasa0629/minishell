/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:39:10 by hyap              #+#    #+#             */
/*   Updated: 2022/09/01 09:30:03 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_executor(t_data *data)
{
	t_list		*seclst;
	t_list		*ellst;

	seclst = data->seclst;
	data->pipein = -1;
	data->pipeout = -1;
	data->tmpstdin = -1;
	data->tmpstdout = -1;
	data->running_cmds = 1;
	g_status.in_cmds = 1;
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
	while (waitpid(-1, &(g_status.status), 0) > 0)
		;
	g_status.status = WEXITSTATUS(g_status.status);
}
