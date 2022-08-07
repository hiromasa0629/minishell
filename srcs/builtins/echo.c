/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:02:35 by hyap              #+#    #+#             */
/*   Updated: 2022/08/07 21:01:26 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_exec *exec)
{
	int	has_nl;
	int	i;

	i = 1;
	has_nl = 1;
	if (ft_strncmp(*(exec->args), "-n", 2) == 0)
		has_nl = 0;
	if (!has_nl)
		i++;
	while ((exec->args)[i])
		printf("%s", (exec->args)[i++]);
	if (has_nl)
		printf("\n");
}