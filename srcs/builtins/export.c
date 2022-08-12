/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:19:34 by hyap              #+#    #+#             */
/*   Updated: 2022/08/12 11:34:40 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_valid_key(char *s)
{
	t_helper	h;

	h.condone = 0;
	h.condtwo = 0;
	if (ft_isalpha(*s) && !ft_has_special_export(s))
		h.condone = 1;
	while (*s)
		if (*(s)++ == '=')
			h.condtwo = 1;
	if (h.condone && h.condtwo)
		return (1);
	return (0);
}

void	realloc_envp_export(t_data *data, int *i, char **dptr)
{
	t_helper	h;

	while ((data->envp)[++(*i)])
	{
		h.len = ft_strlen((data->envp)[*i]);
		h.line = (char *)malloc(sizeof(char) * (h.len + 1));
		ft_strlcpy(h.line, (data->envp)[*i], h.len + 1);
		(h.line)[h.len] = '\0';
		(dptr)[*i] = h.line;
	}
}

void	add_one_env(t_data *data, char *s)
{
	t_helper	h;

	h.i = 0;
	while ((data->envp)[h.i])
		h.i++;
	h.dptr = (char **)malloc(sizeof(char *) * (h.i + 2));
	(h.dptr)[h.i + 1] = NULL;
	h.i = -1;
	if (!data->env_edited)
		realloc_envp_export(data, &h.i, h.dptr);
	else
		while ((data->envp)[++h.i])
			(h.dptr)[h.i] = (data->envp)[h.i];
	(h.dptr)[h.i++] = s;
	if (data->env_edited)
		free(data->envp);
	data->env_edited = 1;
	data->envp = h.dptr;
}

void	ft_export(t_data *data, t_list *cmdlst)
{
	t_helper	h;
	t_cmd		*cmd;

	if (((t_cmd *)cmdlst->content)->type == TYPE_CMD)
		cmdlst = cmdlst->next;
	while (cmdlst)
	{
		cmd = (t_cmd *)cmdlst->content;
		if (check_valid_key(cmd->s))
		{
			h.line = (char *)malloc(sizeof(char) * (ft_strlen(cmd->s) + 1));
			(h.line)[ft_strlen(cmd->s)] = '\0';
			h.i = -1;
			while ((cmd->s)[++h.i])
				(h.line)[h.i] = (cmd->s)[h.i];
			add_one_env(data, h.line);
		}
		else
			builtins_error("Syntax error near '='\n");
		cmdlst = cmdlst->next;
	}
}
