/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:05:54 by hyap              #+#    #+#             */
/*   Updated: 2022/09/01 09:35:01 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_data *data)
{
	char	**envp;
	char	*s;
	int		i;

	envp = data->envp;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			s = envp[i];
			while (*s != '=')
				s++;
			if (*s == '=')
				s++;
			printf("%s\n", s);
		}
		i++;
	}
	g_status.status = 0;
}
