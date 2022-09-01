/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:21:58 by hyap              #+#    #+#             */
/*   Updated: 2022/09/01 09:28:38 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	new_env_len(t_data *data, char *s)
{
	t_helper	h;

	h.i = 0;
	h.len = 0;
	while ((data->envp)[h.i])
		if (ft_strncmp((data->envp)[h.i++], s, ft_strlen(s)) != 0)
			h.len++;
	return (h.len);
}

void	realloc_envp_unset(t_data *data, char **dptr, char *s)
{
	t_helper	h;

	h.i = 0;
	h.j = 0;
	while ((data->envp)[h.i])
	{
		if (ft_strncmp((data->envp)[h.i], s, ft_strlen(s)) == 0)
			free((data->envp)[h.i++]);
		if (!(data->envp)[h.i])
			break ;
		h.len = ft_strlen((data->envp)[h.i]);
		h.line = (char *)malloc(sizeof(char) * (h.len + 1));
		ft_strlcpy(h.line, (data->envp)[h.i], h.len + 1);
		(h.line)[h.len] = '\0';
		(dptr)[h.j] = h.line;
		h.i++;
		h.j++;
	}
}

void	remove_one_env(t_data *data, char *s)
{
	t_helper	h;

	h.len = new_env_len(data, s);
	h.dptr = (char **)malloc(sizeof(char *) * (h.len + 1));
	(h.dptr)[h.len] = NULL;
	realloc_envp_unset(data, h.dptr, s);
	if (data->env_edited)
		free(data->envp);
	data->env_edited = 1;
	data->envp = h.dptr;
}

int	is_key_exist(t_data *data, char *s)
{
	t_helper	h;

	h.i = 0;
	while ((data->envp)[h.i])
	{
		h.j = 0;
		while ((data->envp)[h.i][h.j])
		{
			if ((data->envp)[h.i][h.j] != s[h.j] && s[h.j] != '\0')
				break ;
			if ((data->envp)[h.i][h.j] == '=' && s[h.j] == '\0')
				return (1);
			h.j++;
		}
		h.i++;
	}
	return (0);
}

void	ft_unset(t_data *data, t_list *cmdlst)
{
	t_cmd		*cmd;

	if (((t_cmd *)cmdlst->content)->type == TYPE_CMD)
		cmdlst = cmdlst->next;
	while (cmdlst)
	{
		cmd = (t_cmd *)cmdlst->content;
		if (!ft_isalpha((cmd->s)[0]) || ft_has_special_unset(cmd->s))
		{
			ft_putstr_fd(2, "Invalid identifier\n");
			g_status.status = 1;
			return ;
		}
		if (is_key_exist(data, cmd->s))
			remove_one_env(data, cmd->s);
		cmdlst = cmdlst->next;
	}
}
