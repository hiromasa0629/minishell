/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:19:49 by hyap              #+#    #+#             */
/*   Updated: 2022/09/05 14:10:15 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_data *data, t_list *cmdlst)
{
	t_helper	h;

	if (((t_cmd *)cmdlst->content)->type == TYPE_CMD)
		cmdlst = cmdlst->next;
	ft_putstr_fd(2, "exit\n");
	if (!cmdlst)
		exit_error(data, 0);
	if (!ft_isnum((((t_cmd *)cmdlst->content)->s)[0]))
	{
		builtins_error("Numeric argument required\n");
		exit_error(data, 255);
	}
	g_status = ft_atoi(((t_cmd *)cmdlst->content)->s);
	h.len = 0;
	while (cmdlst)
	{
		h.len++;
		cmdlst = cmdlst->next;
	}
	if (h.len > 1)
		builtins_error("Too many arguments\n");
	else
		exit_error(data, g_status);
}
