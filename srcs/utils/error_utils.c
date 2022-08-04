/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:55:19 by hyap              #+#    #+#             */
/*   Updated: 2022/08/04 16:33:44 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_good_pipes(char *s)
{
	int	i;
	int	count;
	int	quote;

	i = 0;
	quote = 0;
	if (s[i] == '|')
		return (0);
	while (s[i])
	{
		count = 0;
		if (ft_isquotes(s[i]))
			check_in_quotes(s[i], &quote);
		while (s[i] == '|' && s[i] && quote == 0)
		{
			count++;
			i++;
		}
		if (count > 2 || !s[i])
			return (0);
		i++;
	}
	return (1);
}

int	is_good_quotes(char *s)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (ft_isquotes(s[i]))
			check_in_quotes(s[i], &quote);
		i++;
	}
	if (quote != 0)
		return (0);
	return (1);
}

int	is_good_schar(char *s)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (ft_isquotes(s[i]))
			check_in_quotes(s[i], &quote);
		if ((s[i] == '\\' || s[i] == ';') && quote == 0)
			return (0);
		i++;
	}
	return (1);
}

int	is_good_operator(char *s)
{
	int	i;
	int	j;
	int	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (ft_isquotes(s[i]))
			check_in_quotes(s[i], &quote);
		if (!is_valid_redirectop(s, &i, quote))
			return (0);
		if (ft_isredirectop(s[i]))
		{
			j = 0;
			while (ft_isspace(s[i + 1 + j]))
				if (s[i + 1 + j] != '|' && s[i + 1 + (j++)])
					break ;
			if (s[i + 1 + j] == '|' || !s[i + 1 + j])
				return (0);
		}
		i++;
	}
	return (1);
}

int	is_good(char *s)
{
	int		err_code;

	err_code = 1;
	if (!is_good_pipes(s))
		err_code = PIPES_ERR;
	else if (!is_good_quotes(s))
		err_code = QUOTES_ERR;
	else if (!is_good_schar(s))
		err_code = SCHAR_ERR;
	else if (!is_good_operator(s))
		err_code = OP_ERR;
	if (err_code != 1)
	{
		free(s);
		print_err(error_msg(err_code), prompt_error_readline);
		return (0);
	}
	return (err_code);
}
