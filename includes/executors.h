/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:58:45 by hyap              #+#    #+#             */
/*   Updated: 2022/08/08 15:09:07 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTORS_H
# define EXECUTORS_H
# include "./clib.h"
# include "./utils.h"

t_exec	*construct_execve(t_list *ellst, char **envp);
void	ft_execve(t_list *ellst, char **envp, int fileout);
void	ft_run_ele(t_list *ellst, t_data *data);
void	run_builtins(t_data *data, t_list *ellst);


/* Main */
void	ft_executor(t_data *data);

#endif