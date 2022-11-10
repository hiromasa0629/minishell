/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_five.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:27:08 by hyap              #+#    #+#             */
/*   Updated: 2022/11/10 13:56:33 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	sl;

	if (!dest || !src)
		return (0);
	sl = ft_strlen((char *)src);
	i = 0;
	if (size == 0)
		return (sl);
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (sl);
}

void	ft_putstr_fd(int fd, char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		write(fd, &s[i++], 1);
}

int	ft_atoi(const char *s)
{
	int	i;
	int	ans;
	int	res;

	ans = 1;
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			ans = ans * -1;
		i++;
	}
	res = 0;
	while (ft_isnum(s[i]))
		res = (res * 10) + (s[i++] - '0');
	ans = ans * res;
	return (ans);
}

void	exit_error(t_data *data, int err)
{
	int	i;

	i = 0;
	while ((data->envp)[i])
		free((data->envp)[i++]);
	free(data->envp);
	free_all(data);
	exit(err);
}

int	ft_has_special_unset(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isalpha(s[i]) && !ft_isnum(s[i]) && s[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
