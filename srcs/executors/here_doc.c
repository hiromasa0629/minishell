/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:11:51 by hyap              #+#    #+#             */
/*   Updated: 2022/08/12 11:58:21 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_string(char *line, int *i, t_data *data)
{
	t_helper	h;

	h.len = 0;
	h.j = *i;
	while (ft_isalpha(line[*i]) || ft_isnum(line[*i]))
	{
		h.len++;
		(*i)++;
	}
	h.i = 0;
	while ((data->envp)[h.i])
	{
		if (ft_strncmp((data->envp)[h.i], &line[h.j], h.len) == 0)
		{
			h.line = (data->envp)[h.i];
			while (*(h.line) != '=')
				(h.line)++;
			if (*(h.line) == '=')
				(h.line)++;
			return (h.line);
		}
		h.i++;
	}
	return (NULL);
}

int	new_line_length(char *line, t_data *data)
{
	t_helper	h;

	h.len = 0;
	h.i = 0;
	while (line[h.i])
	{
		if (line[h.i] == '$' && ft_isalpha(line[h.i + 1]))
		{
			h.i++;
			h.len += ft_strlen(get_env_string(line, &(h.i), data));
		}
		else
		{
			h.i++;
			h.len++;
		}
	}
	return (h.len);
}

char	*store_new_line(char *line, t_data *data)
{
	t_helper	h;

	h.len = new_line_length(line, data);
	h.line = (char *)malloc(sizeof(char) * (h.len + 1));
	h.i = 0;
	h.k = 0;
	while (line[h.i])
	{
		h.j = 0;
		if (line[h.i] == '$' && ft_isalpha(line[h.i + 1]))
		{
			h.i++;
			h.linetwo = get_env_string(line, &(h.i), data);
			if (!h.linetwo)
				continue ;
			while ((h.linetwo)[h.j])
				(h.line)[h.k++] = (h.linetwo)[h.j++];
		}
		else
			(h.line)[h.k++] = line[h.i++];
	}
	return (h.line);
}

char	*get_delimiter(t_list *ellst)
{
	while (ellst)
	{
		if (((t_element *)ellst->content)->type == TYPE_DELIMITER)
			return (((t_element *)ellst->content)->ele);
		ellst = ellst->next;
	}
	return (NULL);
}

int	ft_heredoc(t_list *ellst, t_data *data)
{
	t_helper	h;
	char		*new_line;

	h.tmplst = ellst;
	pipe(h.fd);
	h.linetwo = get_delimiter(ellst);
	h.line = readline("heredoc>");
	while (ft_strncmp(h.line, h.linetwo, ft_strlen(h.linetwo)) != 0)
	{
		if (!h.line)
			break ;
		new_line = store_new_line(h.line, data);
		free(h.line);
		write((h.fd)[1], new_line, ft_strlen(new_line));
		write((h.fd)[1], "\n", 1);
		free(new_line);
		h.line = readline("heredoc>");
	}
	close((h.fd)[1]);
	return ((h.fd)[0]);
}
