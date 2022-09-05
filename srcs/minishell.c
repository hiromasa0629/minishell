/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:37:56 by hyap              #+#    #+#             */
/*   Updated: 2022/09/05 14:14:53 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	realloc_initial_envp(t_data *data)
{
	t_helper	h;

	h.i = 0;
	while ((data->envp)[h.i])
		h.i++;
	h.dptr = (char **)malloc(sizeof(char *) * (h.i + 1));
	(h.dptr)[h.i] = NULL;
	h.i = 0;
	while ((data->envp)[h.i])
	{
		h.len = ft_strlen((data->envp)[h.i]);
		h.line = (char *)malloc(sizeof(char) * (h.len + 1));
		(h.line)[h.len] = '\0';
		h.j = -1;
		while ((data->envp)[h.i][++h.j])
			(h.line)[h.j] = (data->envp)[h.i][h.j];
		(h.dptr)[h.i] = h.line;
		h.i++;
	}
	data->envp = h.dptr;
	data->env_edited = 1;
}

void	ft_tester_minishell(t_data *data, char *argv)
{
	eof_exit(argv);
	ft_add_history(argv);
	if (!is_good(argv, data))
	{
		g_status = 1;
		return ;
	}
	realloc_initial_envp(data);
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
		register_signal();
		data->running_cmds = 0;
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
		realloc_initial_envp(data);
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
	data.envp = envp;
	data.env_edited = 0;
	data.is_tester = 0;
	data.running_cmds = 0;
	g_status = 0;
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		data.is_tester = 1;
		ft_tester_minishell(&data, av[2]);
		exit(g_status);
	}
	else
		ft_minishell(&data);
	return (0);
}
