/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 21:02:16 by hyap              #+#    #+#             */
/*   Updated: 2022/08/13 09:53:38 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_files(t_helper *h)
{
	if (h->tmpfilein > -1)
	{
		dup2(h->tmpfilein, 0);
		close(h->filein);
		close(h->tmpfilein);
	}
	if (h->tmpfileout > -1)
	{	
		dup2(h->tmpfileout, 1);
		close(h->fileout);
		close(h->tmpfileout);
	}
}

void	duptwo_files(t_helper *h)
{
	if (h->filein > -1)
	{
		h->tmpfilein = dup(STDIN_FILENO);
		dup2(h->filein, STDIN_FILENO);
	}
	if (h->fileout > -1)
	{
		h->tmpfileout = dup(STDOUT_FILENO);
		dup2(h->fileout, STDOUT_FILENO);
	}
}

int	ft_has_heredoc(t_list *ellst)
{
	t_element	*el;

	while (ellst)
	{
		el = (t_element *)ellst->content;
		if (el->type == TYPE_REDIRECT && el->red_type == RED_HEREDOC)
			return (1);
		ellst = ellst->next;
	}
	return (0);
}

void	pipe_n_fork(t_helper *h, t_data *data, t_list *ellst)
{
	if (data->sec_count > 1)
	{
		if (pipe(h->fd) < 0)
			perror("Child pipe");
	}
	if (data->sec_count > 1 || !ft_isimplemented(ellst))
	{
		h->pid = fork();
		if (h->pid < 0)
			perror("Child fork");
	}
}

void	init_fd_helper(t_helper *h)
{
	h->filein = -1;
	h->fileout = -1;
	h->tmpfilein = -1;
	h->tmpfileout = -1;
}
