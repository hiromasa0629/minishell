/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 21:36:45 by hyap              #+#    #+#             */
/*   Updated: 2022/10/13 14:18:41 by hyap             ###   ########.fr       */
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

void	register_signal(void)
{
	t_termios	termios;
	int			rc;

	rc = tcgetattr(0, &termios);
	termios.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &termios);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
