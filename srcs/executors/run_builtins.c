/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 16:25:45 by hyap              #+#    #+#             */
/*   Updated: 2022/08/07 20:59:53 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_builtins_cmd(char *s)
{
	char	*tmp;

	tmp = NULL;
	while (*s)
	{
		if (*s == '/')
			tmp = s + 1;
		s++;
	}
	return (tmp);
}

void	run_builtins(t_data *data, t_exec *exec)
{
	char	*s;

	s = get_builtins_cmd(exec->b_path);
	if (ft_strncmp(s, "echo", 4) == 0)
		ft_echo(exec);
	if (ft_strncmp(s, "cd", 2) == 0)
		return ;
	if (ft_strncmp(s, "pwd", 3) == 0)
		ft_pwd(data);
	if (ft_strncmp(s, "export", 6) == 0)
		ft_export(data, exec);
	if (ft_strncmp(s, "unset", 5) == 0)
		return ;
	if (ft_strncmp(s, "env", 3) == 0)
		ft_env(data);
}