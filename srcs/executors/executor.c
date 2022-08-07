/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:39:10 by hyap              #+#    #+#             */
/*   Updated: 2022/08/07 20:38:51 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_executor(t_data *data, char **envp)
{
	t_list		*seclst;

	seclst = data->seclst;
	while (seclst)
	{
		ft_run_ele(((t_section *)seclst->content)->ellst, envp, data);
		seclst = seclst->next;
	}
}
