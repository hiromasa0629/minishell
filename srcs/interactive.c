/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 21:36:45 by hyap              #+#    #+#             */
/*   Updated: 2022/09/01 15:35:28 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int signum)
{
	(void)signum;
	prompt_new_readline();
}

void	eof_exit(char *s)
{
	if (!s)
	{
		ft_putstr_fd(2, "exit\n");
		exit(1);
	}
}

void	handle_sigquit(int signum)
{
	(void)signum;
	if (g_status.in_cmds)
	{
		ft_putstr_fd(1, "Quit: 3\n");
		g_status.status = 131;
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	register_signal(void)
{
	t_termios	termios;
	int			rc;

	rc = tcgetattr(0, &termios);
	termios.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &termios);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
