/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:37:19 by hyap              #+#    #+#             */
/*   Updated: 2022/08/03 12:44:06 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	has_open_quotes(char **s)
{
	int	i;

	i = 0;
	while (ft_isspace(**s))
		(*s)++;
	while (s[i] && !ft_isspace((*s)[i]))
	{
		if (ft_isquotes((*s)[i]))
			return (1);
		i++;
	}
	return (0);
}

void	check_valid_quotes(char *s)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (ft_isquotes(s[i]))
		{
			if (s[i] == quote)
				quote = 0;
			else
				quote = s[i];
		}
		i++;
	}
	if (quote != 0)
		print_err("Unclosed quotes", prompt_error_readline);
}

// void	count_quotes_length(char *s, int *len, int *i)
// {
// 	int	quote;
// 	int	has_closing;

// 	quote = s[(*i)++];
// 	while (s[*i] && s[*i] != quote)
// 	{
// 		(*len)++;
// 		(*i)++;
// 	}
// 	if (s[*i] == quote)
// 		(*i)++;
// }

void	store_tmp_quote(char **s, int *quote)
{
	if (**s == *quote)
		(*s)++;
	if (ft_isquotes(**s))
	{
		*quote = **s;
		(*s)++;
	}
}

char	*string_quotes_mem(char *s)
{
	char	*str;
	char	*tmp_s;
	int		len;
	int		i;
	int		quote;

	len = 0;
	i = 0;
	quote = -1;
	tmp_s = s;
	while (ft_isspace(*tmp_s))
		tmp_s++;
	while (*tmp_s && !ft_isspace(*tmp_s))
	{
		if (!ft_isquotes(*tmp_s) || (*tmp_s != quote && quote != -1))
		{
			tmp_s++;
			len++;
		}
		else
			store_tmp_quote(&tmp_s, &quote);
			// count_quotes_length(*s, &len, &i);
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	return (str);
}

char	*store_quotes_string(char **s)
{
	int		i;
	int		quote;
	char	*str;

	str = string_quotes_mem(*s);
	i = 0;
	quote = -1;
	while (ft_isspace(**s))
		(*s)++;
	while (**s && !ft_isspace(**s))
	{
		if (!ft_isquotes(**s) || (**s != quote && quote != -1))
		{
			str[i++] = **s;
			(*s)++;
		}
		else
			store_tmp_quote(s, &quote);
	}
	while (ft_isspace(**s))
		(*s)++;
	return (str);
}
