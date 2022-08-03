/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:06:47 by hyap              #+#    #+#             */
/*   Updated: 2022/08/03 16:28:15 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]) != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' \
		|| c == ' ')
		return (1);
	return (0);
}

int	ft_isquotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return 0;
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	check_in_quotes(char c, int *quote)
{
	if (c == *quote && *quote != 0)
		*quote = 0;
	else if (*quote == 0)
		*quote = c;
}

char	ft_isredirectop(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	has_redirectop(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		if (ft_isredirectop(s[i++]))
			return (1);
	return (0);
}