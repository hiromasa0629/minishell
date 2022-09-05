/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:22:07 by hyap              #+#    #+#             */
/*   Updated: 2022/09/05 14:09:54 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_wd(void)
{
	char	tmp[MAXPATHLEN];
	char	*line;

	if (getcwd(tmp, MAXPATHLEN) == NULL)
		perror("getcwd error");
	else
	{
		line = tmp;
		return (line);
	}
	return (NULL);
}

char	*store_new_pwd(void)
{
	t_helper	h;
	char		*tmp;

	tmp = "PWD=";
	h.linetwo = get_wd();
	h.len = ft_strlen(h.linetwo) + ft_strlen(tmp);
	h.line = (char *)malloc(sizeof(char) * (h.len + 1));
	(h.line)[h.len] = '\0';
	h.i = -1;
	while (tmp[++h.i])
		(h.line)[h.i] = tmp[h.i];
	h.j = 0;
	while ((h.linetwo)[h.j])
		(h.line)[h.i++] = (h.linetwo)[h.j++];
	return (h.line);
}

void	edit_env_pwd(t_data *data)
{
	t_helper	h;

	h.i = 0;
	h.line = store_new_pwd();
	while ((data->envp)[h.i])
	{
		if (ft_strncmp((data->envp)[h.i], "PWD=", 4) != 0)
			h.i++;
		else
			break ;
	}
	if (data->env_edited)
		free((data->envp)[h.i]);
	(data->envp)[h.i] = h.line;
}

char	*sliced_path(void)
{
	char		tmp[MAXPATHLEN];
	t_helper	h;

	h.i = 0;
	h.count = 0;
	if (getcwd(tmp, MAXPATHLEN) == NULL)
		perror("getcwd error");
	if (errno != 0)
		return (NULL);
	h.line = tmp;
	while ((h.line)[h.i])
	{
		if ((h.line)[h.i] == '/')
			h.count++;
		if (h.count > 2)
			break ;
		h.i++;
	}
	h.linetwo = (char *)malloc(sizeof(char) * (h.i + 1));
	(h.linetwo)[h.i] = '\0';
	h.j = -1;
	while (++h.j < h.i)
		(h.linetwo)[h.j] = (h.line)[h.j];
	return (h.linetwo);
}

void	ft_cd(t_list *cmdlst, t_data *data)
{
	char	*path;

	path = NULL;
	if (((t_cmd *)cmdlst->content)->type == TYPE_CMD)
		cmdlst = cmdlst->next;
	if (!cmdlst || ft_strncmp(((t_cmd *)cmdlst->content)->s, "~", 1) == 0)
		path = sliced_path();
	else
		path = ((t_cmd *)cmdlst->content)->s;
	if (chdir(path) == -1)
	{
		g_status = errno;
		perror("cd");
	}
	else
	{
		g_status = 0;
		edit_env_pwd(data);
	}
}
