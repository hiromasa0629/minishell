/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:21:03 by hyap              #+#    #+#             */
/*   Updated: 2022/08/01 19:48:02 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	string_count(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (ft_isspace(s[i]))
		i++;
	if (!s[i])
		count = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]) && s[i + 1] && !ft_isspace(s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

// int	has_open_quotes(char **s)
// {
// 	int	i;

// 	i = 0;
// 	while (ft_isspace(**s))
// 		(*s)++;
// 	while (s[i] && !ft_isspace(s[i]))
// 	{
// 		if (ft_isquotes(s[i]))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// char	*store_quotes_string(char **s)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	while ((*s)[i] && !ft_isquotes((*s)[i]))
// 		i++;
// 	str = (char *)malloc(sizeof(char) * (i + 1));
// 	str[i] = '\0';
// 	i = 0;
// 	while (**s && !ft_isquotes(**s))
// 	{
// 		str[i++] = **s;
// 		(*s)++;
// 	}
// 	while (ft_isspace(**s))
// 		(*s)++;
// 	return (str);
// }

// char	*store_string(char **s)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	while (ft_isspace(**s))
// 		(*s)++;
// 	while ((*s)[i] && !ft_isspace((*s)[i]))
// 		i++;
// 	if (i == 0)
// 		return (NULL);
// 	str = (char *)malloc(sizeof(char) * (i + 1));
// 	str[i] = '\0';
// 	i = 0;
// 	while (**s && !ft_isspace(**s))
// 	{
// 		str[i++] = **s;
// 		(*s)++;
// 	}
// 	while (ft_isspace(**s))
// 		(*s)++;
// 	return (str);
// }

char	**ft_split(char *s)
{
	char	**split;
	int		count;
	int		i;

	if (!s)
		return (NULL);
	check_valid_quotes(s);
	count = string_count(s);
	split = (char **)malloc(sizeof(char *) * (count + 1));
	split[count] = NULL;
	i = 0;
	while (*s)
	{
		split[i++] = store_quotes_string(&s);
	}
	return (split);
}
