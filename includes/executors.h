/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:58:45 by hyap              #+#    #+#             */
/*   Updated: 2022/08/09 20:45:36 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTORS_H
# define EXECUTORS_H
# include "./clib.h"
# include "./utils.h"

t_exec	*construct_execve(t_list *ellst, char **envp);
void	ft_execve(t_list *ellst, char **envp);
void	ft_run_ele(t_list *ellst, t_data *data, t_list *seclst);
void	run_builtins(t_data *data, t_list *ellst);
void	close_files(t_helper *h);
void	pipe_n_fork(t_helper *h, t_data *data, t_list *ellst);
void	duptwo_files(t_helper *h);
void	init_fd_helper(t_helper *h);
void	mulsec_duptwo_files(t_helper *h, t_data *data);
int		ft_has_heredoc(t_list *ellst);
int		ft_heredoc(t_list *ellst, t_data *data);


/* Main */
void	ft_executor(t_data *data);

#endif