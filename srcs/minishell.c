/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:37:56 by hyap              #+#    #+#             */
/*   Updated: 2022/08/03 11:29:25 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_line(t_data *data, char *line)
{
	t_list 		*tmp;
	t_section	*section;

	split_pipe(data, line);
	ft_lstiter(data->seclst, print_sec_content);
	tmp = data->seclst;
	while (tmp)
	{
		section = (t_section *)tmp->content; 
		split_section(&section);
		ft_lstiter(((t_section *)tmp->content)->ellst, print_ele_content);
		tmp = tmp->next;
	}
}

int	main(void)
{
	char	*line;
	t_data	data;

	register_signal();
	while (1)
	{
		printf("%s", WHITE);
		line = readline("minishell>");
		eof_exit(line);
		my_add_history(line);
		if (!is_good(line))
			continue;
		handle_line(&data, line);
		free_all(&data);
		free(line);
	}
	return (0);
}
