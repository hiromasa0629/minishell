/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:59:51 by hyap              #+#    #+#             */
/*   Updated: 2022/08/04 20:51:34 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parser(t_data *data)
{
	t_list		*seclst;
	t_section	*section;

	seclst = data->seclst;
	while (seclst)
	{
		section = (t_section *)seclst->content;
		expand_section(&section, data->envp);
		ft_lstiter(((t_section *)seclst->content)->ellst, print_ele_content);
		seclst = seclst->next;
	}
}