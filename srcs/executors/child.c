/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:24:30 by hyap              #+#    #+#             */
/*   Updated: 2022/08/07 21:13:41 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_file(t_helper *h, t_list *ellst)
{
	t_element *el;
	t_element *p_el;

	while (ellst)
	{
		el = (t_element *)ellst->content;
		if (el->type == TYPE_FILE)
		{
			p_el = (t_element *)ellst->prev->content;
			if (p_el->red_type == RED_INPUT)
			{
				h->filein = open(el->ele, O_RDONLY);
				dup2(h->filein, STDIN_FILENO);
			}
			else if (p_el->red_type == RED_OUTPUT && \
				p_el->red_mode == MODE_APPEND)
				h->fileout = open(el->ele, O_WRONLY | O_CREAT | O_APPEND, 0777);
			else if (p_el->red_type == RED_OUTPUT && \
				p_el->red_mode == MODE_TRUNC)
				h->fileout = open(el->ele, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		}
		ellst = ellst->next;
	}
}

void	pipe_n_fork(t_helper *h)
{
	if (pipe(h->fd) < 0)
		perror("Child pipe");
	h->pid = fork();
	if (h->pid < 0)
		perror("Child fork");
}

void	pre_ft_execve(t_data *data, t_list *ellst, char **envp, t_helper par_h)
{
	t_helper	h;

	pipe_n_fork(&h);
	if (h.pid == 0)
	{
		close(h.fd[0]);
		if (data->sec_count > 1 && par_h.filein > -1)
			dup2(h.fd[1], STDOUT_FILENO);
		else 
			close(h.fd[1]);
		ft_execve(data, ellst, envp, par_h.fileout);
	}
	else
	{
		close(h.fd[1]);
		if (data->sec_count > 1 && par_h.filein > -1)
			dup2(h.fd[0], STDIN_FILENO);
		else
			close(h.fd[0]);
		waitpid(h.pid, NULL, 0);
	}
}

void	ft_run_ele(t_list *ellst, char **envp, t_data *data)
{
	t_helper	h;

	h.filein = -1;
	h.fileout = -1;
	open_file(&h, ellst);
	if (h.filein > -1)
		dup2(h.filein, STDIN_FILENO);
	if (ft_cmd_exist(ellst))
		pre_ft_execve(data, ellst, envp, h);
	if (h.filein > -1)
		close(h.filein);
	if (h.fileout > -1)
		close(h.fileout);
}