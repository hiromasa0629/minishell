/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:02:35 by hyap              #+#    #+#             */
/*   Updated: 2022/08/08 14:11:31 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_list *cmdlst)
{
	int			has_nl;
	t_helper	h;

	h.i = 1;
	has_nl = 1;
	h.tmplst = cmdlst->next;
	while (h.tmplst)
	{
		if (((t_cmd *)h.tmplst->content)->type == TYPE_FLAG)
			if (ft_strncmp(((t_cmd *)h.tmplst->content)->s, "-n", 2) == 0)
				has_nl = 0;
		if (((t_cmd *)h.tmplst->content)->type == TYPE_ARG)
			break ;
		h.tmplst = h.tmplst->next;
	}
	while (h.tmplst)
	{
		printf("%s", ((t_cmd *)h.tmplst->content)->s);
		if (h.tmplst->next)
			printf("%c", ' ');
		h.tmplst = h.tmplst->next;
	}
	if (has_nl)
		printf("\n");
	status = 0;
}