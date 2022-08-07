/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:57:50 by hyap              #+#    #+#             */
/*   Updated: 2022/08/07 20:47:48 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	loop_split_ispipe(char c, int quote)
{
	if ((c && c != '|') || (c && c == '|' && quote != 0))
		return (1);
	return (0);
}

int	section_len(char *s)
{
	int	i;
	int	count;
	int	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (loop_split_ispipe(s[i], quote))
	{
		if (ft_isquotes(s[i]))
			check_in_quotes(s[i], &quote);
		count++;
		i++;
	}
	return (count);
}

char	*create_sec(char **line)
{
	char	*s;
	int		sec_len;
	int		i;
	int		quote;

	sec_len = section_len(*line);
	s = (char *)malloc(sizeof(char) * (sec_len + 1));
	// printf("size: %d\n", sec_len + 1);
	s[sec_len] = '\0';
	i = 0;
	quote = 0;
	while (loop_split_ispipe(**line, quote))
	{
		if (ft_isquotes(**line))
			check_in_quotes(**line, &quote);
		s[i++] = **line;
		(*line)++;
	}
	return (s);
}

void	store_section(t_data *data, char **line)
{
	t_section	*section;

	section = (t_section *)malloc(sizeof(t_section));
	section->sec = create_sec(line);
	section->ellst = NULL;
	section->numth = data->sec_count - 1;
	ft_lstadd_back(&data->seclst, ft_lstnew(section));
	data->sec_count++;
}

void	split_pipe(t_data *data, char *line)
{
	int		pos;
	int		start;
	int		quote;

	pos = 0;
	quote = 0;
	start = 0;
	data->sec_count = 1;
	data->seclst = NULL;
	while (*line)
	{
		store_section(data, &line);
		while (*line == '|')
			line++;
	}
}
