/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:24:30 by hyap              #+#    #+#             */
/*   Updated: 2022/08/26 19:48:04 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_files(t_helper *h, t_list *ellst, t_data *data)
{
	t_element	*el;
	t_element	*p_el;

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

void	multiple_sections_child(t_helper *h, t_data *data, t_list *seclst)
{
	t_list	*ellst;

	ellst = ((t_section *)seclst->content)->ellst;
	close((h->fd)[0]);
	if (data->tmpstdin > -1)
		dup2(data->tmpstdin, STDIN_FILENO);
	if (h->filein > -1)
		dup2(h->filein, STDIN_FILENO);
	if (seclst->next && h->fileout < 0)
		dup2((h->fd)[1], STDOUT_FILENO);
	else if (h->fileout > -1)
		dup2(h->fileout, STDOUT_FILENO);
	if (ft_isimplemented(ellst))
		run_builtins(data, ellst, -1);
	else
		ft_execve(ellst, data->envp);
	exit(status);
}

void	multiple_sections(t_list *ellst, t_data *data, t_list *seclst)
{
	t_helper	h;

	h.filein = -1;
	h.fileout = -1;
	open_files(&h, ellst, data);
	pipe_n_fork(&h, data, ellst);
	if (h.pid == 0)
		multiple_sections_child(&h, data, seclst);
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
	t_helper	h;

	h.pid = -2;
	init_fd_helper(&h);
	if (!ft_cmd_exist(ellst) && !ft_has_heredoc(ellst))
		return ;
	open_files(&h, ellst, data);
	duptwo_files(&h);
	pipe_n_fork(&h, data, ellst);
	if (h.pid == 0)
	{
		if (!(!ft_cmd_exist(ellst) && ft_has_heredoc(ellst)))
			ft_execve(ellst, data->envp);
		exit(status);
	}
	else if (data->sec_count == 1 && ft_isimplemented(ellst))
	{
		if (h.fileout > -1)
			run_builtins(data, ellst, h.fileout);
		else
			run_builtins(data, ellst, 1);
	}
	close_files(&h);
}
