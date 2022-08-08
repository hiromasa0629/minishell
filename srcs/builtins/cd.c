/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:22:07 by hyap              #+#    #+#             */
/*   Updated: 2022/08/08 16:39:21 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_list *cmdlst)
{
	if (((t_cmd *)cmdlst->content)->type == TYPE_CMD)
		cmdlst = cmdlst->next;
	if (!cmdlst)
		return ;
	if (chdir(((t_cmd *)cmdlst->content)->s) == -1)
	{
		status = errno;
		perror("cd");
	}
	else
		status = 0;
}