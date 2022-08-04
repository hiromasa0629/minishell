/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:51:39 by hyap              #+#    #+#             */
/*   Updated: 2022/08/04 21:40:52 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lexer(t_data *data, char *line)
{
	t_list		*seclst;
	t_section	*section;

	printf("%s============================\n", WHITE);
	split_pipe(data, line);
	ft_lstiter(data->seclst, print_sec_content);
	seclst = data->seclst;
	while (seclst)
	{
		section = (t_section *)seclst->content;
		split_section(&section);
		complete_element(&section);
		ft_lstiter(((t_section *)seclst->content)->ellst, print_ele_content);
		seclst = seclst->next;
	}
	printf("%s============================\n", WHITE);
}
