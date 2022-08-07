/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:37:56 by hyap              #+#    #+#             */
/*   Updated: 2022/08/07 20:42:43 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;

	(void)ac,
	(void)av;
	register_signal();
	data.envp = envp;
	data.env_edited = 0;
	status = 0;
	while (1)
	{
		printf("%s", WHITE);
		line = readline("minishell>");
		eof_exit(line);
		ft_add_history(line);
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			return (0);
		}
		if (!is_good(line))
			return (0);
			// continue ;
		ft_lexer(&data, line, data.envp);
		ft_parser(&data);
		ft_executor(&data, data.envp);
		free_all(&data);
		free(line);
	}
	return (0);
}
