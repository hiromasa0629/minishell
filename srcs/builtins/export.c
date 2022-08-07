/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:19:34 by hyap              #+#    #+#             */
/*   Updated: 2022/08/07 20:34:55 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_valid_key(char *s)
{
	t_helper	h;

	h.condone = 0;
	h.condtwo = 0;
	if (ft_isalpha(*s))
		h.condone = 1;
	while (*s)
		if (*(s)++ == '=')
			h.condtwo = 1;
	if (h.condone && h.condtwo)
		return (1);
	return (0);
}

void	add_one_env(t_data *data, char *s)
{
	t_helper	h;

	h.i = 0;;
	while ((data->envp)[h.i])
		h.i++;
	h.dptr = (char **)malloc(sizeof(char *) * (h.i + 1));
	(h.dptr)[h.i] = NULL;
	h.i = 0;
	while ((data->envp)[h.i])
	{
		(h.dptr)[h.i] = (data->envp)[h.i];
		h.i++;
	}
	(h.dptr)[h.i++] = s;
	if (data->env_edited)
		free(data->envp);
	data->env_edited = 1;
	data->envp = h.dptr;
}

void	ft_export(t_data *data, t_exec *exec)
{
	t_helper	h;

	h.i = 1;
	while ((exec->args)[h.i])
	{
		h.len = ft_strlen((exec->args)[h.i]);
		if (!check_valid_key((exec->args)[h.i]))
		{
			h.i++;
			continue;
		}
		h.j = 0;
		h.line = (char *)malloc(sizeof(char) * (h.len + 1));
		(h.line)[h.len] = '\0';
		while (((exec->args)[h.i])[h.j])
		{
			(h.line)[h.j] = ((exec->args)[h.i])[h.j];
			h.j++;
		}
		add_one_env(data, h.line);
		h.i++;
	}
}