/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_validation_two.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 19:59:39 by hyap              #+#    #+#             */
/*   Updated: 2022/08/07 16:40:51 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	assign_redirect_type(t_element **el)
{
	if (ft_strncmp((*el)->ele, ">>", 2) == 0)
	{
		(*el)->red_type = RED_OUTPUT;
		(*el)->red_mode = MODE_APPEND;
	}
	else if (ft_strncmp((*el)->ele, "<<", 2) == 0)
	{
		(*el)->red_type = RED_HEREDOC;
		(*el)->red_mode = 0;
	}
	else if (ft_strncmp((*el)->ele, ">", 1) == 0)
	{
		(*el)->red_type = RED_OUTPUT;
		(*el)->red_mode = MODE_TRUNC;
	}
	else if (ft_strncmp((*el)->ele, "<", 1) == 0)
	{
		(*el)->red_type = RED_INPUT;
		(*el)->red_mode = 0;
	}
	// printf("(*el)->ele: %s, (*el)->type: %d\n", (*el)->ele, (*el)->red_type);
}

int	ft_has_prev_cmd(t_list *ellst)
{
	while (ellst->prev)
	{
		if (((t_element *)ellst->prev->content)->type == TYPE_CMD)
			return (1);
		ellst = ellst->prev;
	}
	return (0);
}

int	ft_has_prev_arg(t_list *ellst)
{
	while (ellst->prev)
	{
		if (((t_element *)ellst->prev->content)->type == TYPE_ARG)
			return (1);
		ellst = ellst->prev;
	}
	return (0);
}
