/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:25:45 by hyap              #+#    #+#             */
/*   Updated: 2022/08/08 17:14:10 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*construct_cmd(t_list *ellst)
{
	t_cmd		*cmd;
	t_list		*cmdlst;
	t_element	*el;

	cmdlst = NULL;
	while(ellst)
	{
		el = (t_element *)ellst->content;
		if (el->type == TYPE_ARG || el->type == TYPE_CMD || el->type == TYPE_FLAG)
		{
			cmd = (t_cmd *)malloc(sizeof(t_cmd));
			cmd->s = el->ele;
			cmd->type = el->type;
			ft_lstadd_back(&cmdlst, ft_lstnew(cmd));
		}
		ellst = ellst->next;
	}
	return (cmdlst);
}

void	free_cmdlst(t_list *cmdlst)
{
	t_list	*tmp;

	while (cmdlst)
	{
		tmp = cmdlst->next;
		free(cmdlst);
		cmdlst = tmp;
	}
}

void	run_builtins(t_data *data, t_list *ellst)
{
	char	*s;
	t_list	*cmdlst;

	cmdlst = construct_cmd(ellst);
	s = ((t_cmd *)cmdlst->content)->s;
	if (!cmdlst)
		return ;
	if (ft_strncmp(s, "echo", 4) == 0)
		ft_echo(cmdlst);
	if (ft_strncmp(s, "cd", 2) == 0)
		ft_cd(cmdlst);
	if (ft_strncmp(s, "pwd", 3) == 0)
		ft_pwd(data);
	if (ft_strncmp(s, "export", 6) == 0)
		ft_export(data, cmdlst);
	if (ft_strncmp(s, "unset", 5) == 0)
		ft_unset(data, cmdlst);
	if (ft_strncmp(s, "env", 3) == 0)
		ft_env(data);
	free_cmdlst(cmdlst);
}