/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:11:51 by hyap              #+#    #+#             */
/*   Updated: 2022/08/11 22:15:40 by hyap             ###   ########.fr       */
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
			dprintf(2, "h.linetwo: %s\n", h.linetwo);
			if (!h.linetwo)
				continue ;
			while ((h.linetwo)[h.j])
			{
				(h.line)[h.k++]  = (h.linetwo)[h.j++];
				// dprintf(2, "h.line[h.k]: %c, h.linetwo[h.j]: %c\n", (h.line)[h.k - 1], (h.linetwo)[h.j - 1]);
			}
		}
		else
		{
			(h.line)[h.k++] = line[h.i++];
			// dprintf(2, "h.line[h.k]: %c, h.linetwo[h.j]: %c\n", (h.line)[h.k - 1], (h.linetwo)[h.j - 1]);
		}
	}
	dprintf(2, "h.len: %d, h.line: %s\n", h.len, h.line);
	return (h.line);
}

int	ft_heredoc(t_list *ellst, t_data *data)
{
	t_helper	h;
	char		*new_line;

	h.tmplst = ellst;
	pipe(h.fd);
	while (h.tmplst)
	{
		if (((t_element *)h.tmplst->content)->type == TYPE_DELIMITER)
		{
			h.linetwo = ((t_element *)h.tmplst->content)->ele;
			break ;
		}
		h.tmplst = h.tmplst->content;
	}
	h.line = readline("heredoc>");
	if (!h.line)
		return (-1);
	while (ft_strncmp(h.line, h.linetwo, ft_strlen(h.linetwo)) != 0)
	{
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