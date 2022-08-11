/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:39:10 by hyap              #+#    #+#             */
/*   Updated: 2022/08/11 20:51:55 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_executor(t_data *data)
{
	t_list		*seclst;

	seclst = data->seclst;
	data->pipein = -1;
	data->pipeout = -1;
	data->tmpstdin = -1;
	data->tmpstdout = -1;
	while (seclst)
	{
		ft_run_ele(((t_section *)seclst->content)->ellst, data, seclst);
		seclst = seclst->next;
	}
	if (status == 0)
	{
		while (waitpid(-1, &status, 0) > 0)
			;
		status = WEXITSTATUS(status);
	}
}
