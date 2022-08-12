/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:37:56 by hyap              #+#    #+#             */
/*   Updated: 2022/08/12 12:31:29 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_tester_minishell(t_data *data, char *argv)
{
	eof_exit(argv);
	ft_add_history(argv);
	if (!is_good(argv, data))
	{
		status = 1;
		return ;
	}
	ft_lexer(data, argv, data->envp);
	ft_parser(data);
	ft_executor(data);
	free_all(data);
}

void	ft_minishell(t_data *data)
{
	char	*line;

	while (1)
	{
		data->tmpstdin = -1;
		data->tmpstdout = -1;
		line = readline("minishell>");
		eof_exit(line);
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		ft_add_history(line);
		if (!is_good(line, data))
			continue ;
		ft_lexer(data, line, data->envp);
		ft_parser(data);
		ft_executor(data);
		free_all(data);
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac,
	(void)av;
	register_signal();
	data.envp = envp;
	data.env_edited = 0;
	status = 0;
	data.is_tester = 0;
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		data.is_tester = 1;
		ft_tester_minishell(&data, av[2]);
		exit(status);
	}
	else
		ft_minishell(&data);
	return (0);
}
