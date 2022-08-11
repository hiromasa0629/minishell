/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:11:51 by hyap              #+#    #+#             */
/*   Updated: 2022/08/09 19:20:33 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_env_val(char *s, t_data *data, int *i)
{
	t_helper	h;

	h.i = 0;
	h.len = 0;
	while (ft_isnum(s[*i]) || ft_isalpha(s[*i]))
	{
		h.len++;
		(*i)++;
	}
	while ((data->envp)[h.i])
	{
		if (ft_strncmp((data->envp)[h.i], s, h.len) == 0)
		{
			h.line = (data->envp)[h.i];
			while (*(h.line) != '=')
				h.line++;
			if (*(h.line) == '=')
				h.line++;
			return (h.line);
		}
		h.i++;
	}
	return (NULL);
}

int	new_line_length(t_data *data, char *s)
{
	t_helper	h;

	h.i = 0;
	h.len = 0;
	while (s[h.i])
	{
		if (s[h.i] == '$' && (ft_isalpha(s[h.i + 1]) || s[h.i + 1] == '_'))
		{
			h.i++;
			h.len += ft_strlen(find_env_val(s, data, &(h.i)));
		}
		else
		{
			h.i++;
			h.len++;
		}
	}
	return (h.len);
}

char	*store_new_line(char *s, t_data *data)
{
	t_helper	h;

	h.i = 0;
	h.j = 0;
	h.len = new_line_length(data, s);
	h.line = (char *)malloc(sizeof(char) * (h.len + 1));
	(h.line)[h.len] = '\0';
	while (s[h.i])
	{
		if (s[h.i] == '$' && (ft_isalpha(s[h.i + 1]) || s[h.i + 1] == '_'))
		{
			h.i++;
			h.k = 0;
			h.linetwo = find_env_val(&s[h.i], data, &(h.i));
			if (!h.linetwo)
				continue ;
			while ((h.linetwo)[h.k])
				(h.line)[h.j++] = (h.linetwo)[h.k++];
		}
		else
			(h.line)[h.j++] = s[h.i++];
	}
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
	while (ft_strncmp(h.line, h.linetwo, ft_strlen(h.linetwo)) != 0)
	{
		free(h.line);
		new_line = store_new_line(h.line, data);
		write((h.fd)[1], new_line, ft_strlen(new_line));
		write((h.fd)[1], "\n", 1);
		free(new_line);
		h.line = readline("heredoc>");
	}
	free(h.line);
	close((h.fd)[1]);
	return ((h.fd)[0]);
}