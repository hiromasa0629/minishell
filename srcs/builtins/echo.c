/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:02:35 by hyap              #+#    #+#             */
/*   Updated: 2022/09/01 09:28:21 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	store_echo_string(char **newstr, t_list *cmdlst, int has_nl)
{
	t_helper	h;

	h.i = 0;
	while (cmdlst)
	{
		h.j = 0;
		h.line = ((t_cmd *)cmdlst->content)->s;
		while ((h.line)[h.j])
			(*newstr)[h.i++] = (h.line)[h.j++];
		if (cmdlst->next && (((t_cmd *)cmdlst->content)->s)[0])
			(*newstr)[h.i++] = ' ';
		cmdlst = cmdlst->next;
	}
	if (has_nl)
		(*newstr)[h.i++] = '\n';
}

char	*echo_string(t_list	*cmdlst, int has_nl)
{
	t_helper	h;

	h.tmplst = cmdlst;
	h.len = 0;
	while (h.tmplst)
	{
		h.len += ft_strlen(((t_cmd *)h.tmplst->content)->s);
		if (h.tmplst->next && (((t_cmd *)h.tmplst->content)->s)[0])
			h.len++;
		h.tmplst = h.tmplst->next;
	}
	if (has_nl)
		h.len++;
	h.line = (char *)malloc(sizeof(char) * (h.len + 1));
	h.line[h.len] = '\0';
	store_echo_string(&h.line, cmdlst, has_nl);
	return (h.line);
}

char	*ft_echo(t_list *cmdlst)
{
	int			has_nl;
	t_helper	h;

	h.i = 1;
	has_nl = 1;
	h.tmplst = cmdlst->next;
	while (h.tmplst)
	{
		if (((t_cmd *)h.tmplst->content)->type == TYPE_FLAG)
		{
			while (ft_strncmp(((t_cmd *)h.tmplst->content)->s, "-n", 2) == 0)
			{
				has_nl = 0;
				h.tmplst = h.tmplst->next;
				if (!h.tmplst)
					return (NULL);
			}
			break ;
		}
		if (((t_cmd *)h.tmplst->content)->type == TYPE_ARG)
			break ;
		h.tmplst = h.tmplst->next;
	}
	g_status.status = 0;
	return (echo_string(h.tmplst, has_nl));
}
