/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:15:14 by hyap              #+#    #+#             */
/*   Updated: 2022/08/07 21:17:22 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_paths(char **envp)
{
	t_helper	h;
	char		*path;
	char		**paths;

	h.i = 0;
	path = NULL;
	while (envp[h.i])
	{
		if (ft_strncmp(envp[h.i], "PATH=", 5) == 0)
		{
			path = envp[h.i];
			while (*path != '=')
				path++;
			if (*path == '=' && *path)
				path++;
		}
		h.i++;
	}
	paths = ft_split(path, ':');
	return (paths);
}

char	*get_b_path(char **envp, t_list *ellst)
{
	t_helper	h;
	t_element	*el;
	t_stat		st;
	char		**paths;
	int			found;

	paths = get_paths(envp);
	el = (t_element *)ellst->content;
	h.i = 0;
	found = 0;
	while (paths[h.i])
	{
		h.line = concat_two_string(paths[h.i++], el->ele);
		if (stat(h.line, &st) == 0)
		{
			found = 1;
			break ;
		}
		free(h.line);
	}
	if (!found)
		return (NULL);
	return (h.line);
}

void	store_args(t_list *ellst, t_exec **exec)
{
	int			i;
	t_helper	h;

	h.len = 0;
	h.tmplst = ellst;
	while (h.tmplst)
	{
		if (((t_element *)h.tmplst->content)->type == TYPE_ARG || \
			((t_element *)h.tmplst->content)->type == TYPE_FLAG)
			h.len++;
		h.tmplst = h.tmplst->next;
	}
	(*exec)->args = (char **)malloc(sizeof(char *) * (1 + h.len + 1));
	((*exec)->args)[h.len + 1] = NULL;
	i = 0;
	((*exec)->args)[i++] = (*exec)->b_path;
	while (ellst)
	{
		if (((t_element *)ellst->content)->type == TYPE_ARG || \
			((t_element *)ellst->content)->type == TYPE_FLAG)
			((*exec)->args)[i++] = ((t_element *)ellst->content)->ele;
		ellst = ellst->next;
	}
}

t_exec	*construct_execve(t_list *ellst, char **envp)
{
	t_helper	h;
	t_exec		*exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	h.tmplst = ellst;
	while (h.tmplst)
	{
		if (((t_element *)h.tmplst->content)->type == TYPE_CMD)
		{
			exec->b_path = get_b_path(envp, h.tmplst);
			break ;
		}
		h.tmplst = h.tmplst->next;
	}
	ellst = ellst->next;
	exec->args = NULL;
	if (!ellst)
		return (exec);
	store_args(ellst, &exec);
	return (exec);
}

void	ft_execve(t_data *data, t_list *ellst, char **envp, int fileout)
{
	t_exec		*exec;
	t_helper	h;

	exec = construct_execve(ellst, envp);
	if (fileout > -1)
		dup2(fileout, STDOUT_FILENO);
	h.line = exec->b_path;
	h.linetwo = NULL;
printf("line: %s\n", h.line);
	if (h.line)
	{
		while (*(h.line))
		{
			if (*(h.line) == '/')
				h.linetwo = h.line;
			h.line++;
		}
		h.linetwo++;
	}
printf("linetwo: %s\n", h.linetwo);
	if (!ft_isimplemented(h.linetwo))
	{
		printf("!implemented\n");
		if (execve(exec->b_path, exec->args, NULL) == -1)
		{
			status = errno;
			perror("execve");
		}
		else
			status = 0;
	}
	else
	{
		// printf("builtins, %s\n", h.linetwo);
		run_builtins(data, exec);
	}
	free(exec);
}
