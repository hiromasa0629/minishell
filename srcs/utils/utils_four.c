/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_four.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:47:47 by hyap              #+#    #+#             */
/*   Updated: 2022/08/12 12:15:35 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isimplemented(t_list *ellst)
{
	char	*s;

	if (!ellst)
		return (0);
	while (((t_element *)ellst->content)->type != TYPE_CMD)
		ellst = ellst->next;
	if (!ellst)
		return (0);
	s = ((t_element *)ellst->content)->ele;
	if (ft_strncmp(s, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(s, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(s, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(s, "export", 6) == 0)
		return (1);
	if (ft_strncmp(s, "unset", 5) == 0)
		return (1);
	if (ft_strncmp(s, "env", 3) == 0)
		return (1);
	if (ft_strncmp(s, "exit", 4) == 0)
		return (1);
	return (0);
}

char	*concat_two_string(char *one, char *two)
{
	t_helper	h;

	h.len = ft_strlen(one);
	h.lentwo = ft_strlen(two);
	h.line = (char *)malloc(sizeof(char) * (h.len + 1 + h.lentwo + 1));
	(h.line)[h.len + 1 + h.lentwo] = '\0';
	h.i = 0;
	h.j = 0;
	while (one[h.i])
	{
		(h.line)[h.i] = one[h.i];
		h.i++;
	}
	(h.line)[(h.i)++] = '/';
	while (two[h.j])
		(h.line)[(h.i)++] = two[(h.j)++];
	return (h.line);
}

int	ft_numlen(long long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		len ++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*s;
	int			len;
	long long	num;

	num = n;
	len = ft_numlen(n);
	if (n < 0)
		len = len + 1;
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		num = num * -1;
	}
	s[len--] = '\0';
	while (len >= 0)
	{
		s[len--] = (num % 10) + '0';
		if (n < 0 && len < 1)
			break ;
		num = num / 10;
	}
	return (s);
}

int	ft_cmd_exist(t_list *ellst)
{
	while (ellst)
	{
		if (((t_element *)ellst->content)->type == TYPE_CMD)
			return (1);
		ellst = ellst->next;
	}
	return (0);
}
