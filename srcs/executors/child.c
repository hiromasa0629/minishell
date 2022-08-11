/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:24:30 by hyap              #+#    #+#             */
/*   Updated: 2022/08/11 22:17:27 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_files(t_helper *h, t_list *ellst, t_data *data)
{
	t_element *el;
	t_element *p_el;

	while (ellst)
	{
		el = (t_element *)ellst->content;
		if (el->type == TYPE_DELIMITER)
			h->filein = ft_heredoc(ellst, data);
		else if (el->type == TYPE_FILE)
		{
			p_el = (t_element *)ellst->prev->content;
			if (p_el->red_type == RED_INPUT)
				h->filein = open(el->ele, O_RDONLY);
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

void	multiple_sections(t_list *ellst, t_data *data, t_list *seclst)
{
	t_helper	h;

	h.filein = -1;
	h.fileout = -1;
	open_files(&h, ellst, data);
	pipe_n_fork(&h, data, ellst);
	if (h.pid == 0)
	{
		close((h.fd)[0]);
		if (data->tmpstdin > -1)
			dup2(data->tmpstdin, STDIN_FILENO);
		if (h.filein > -1)
			dup2(h.filein, STDIN_FILENO);
		if (seclst->next && h.fileout < 0)
			dup2((h.fd)[1], STDOUT_FILENO);
		else if (h.fileout > -1)
			dup2(h.fileout, STDOUT_FILENO);
		if (ft_isimplemented(ellst))
			run_builtins(data, ellst);
		else
			ft_execve(ellst, data->envp);
		exit(status);
	}
	else
	{
		close((h.fd)[1]);
		if (data->tmpstdin > -1)
			close(data->tmpstdin);
		if (seclst->next && h.fileout < 0)
			data->tmpstdin = (h.fd)[0];
		else
			close((h.fd)[0]);
		if (h.filein > -1)
			close(h.filein);
		if (h.fileout > -1)
			close(h.fileout);
	}
}

void	single_section(t_list *ellst, t_data *data)
{
	t_helper	*h;

	h = (t_helper *)malloc(sizeof(t_helper));
	init_fd_helper(h);
	h->pid = -1;
	open_files(h, ellst, data);
	if (!ft_cmd_exist(ellst))
		return ;
	duptwo_files(h);
	pipe_n_fork(h, data, ellst);
	if (h->pid == 0)
	{
		ft_execve(ellst, data->envp);
		exit(status);
	}
	else if (h->pid == -1)
		run_builtins(data, ellst);
	close_files(h);
	free(h);
}

void	ft_run_ele(t_list *ellst, t_data *data, t_list *seclst)
{
	if (data->sec_count > 1)
		multiple_sections(ellst, data, seclst);
	else
		single_section(ellst, data);
}