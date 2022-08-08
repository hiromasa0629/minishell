/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:59:32 by hyap              #+#    #+#             */
/*   Updated: 2022/08/08 17:14:18 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "./clib.h"
# include "./utils.h"

void	ft_echo(t_list *cmdlst);
void	ft_pwd(t_data *data);
void	ft_env(t_data *data);
void	ft_export(t_data *data, t_list *cmdlst);
void	ft_unset(t_data *data, t_list *cmdlst);
void	ft_cd(t_list *cmdlst);

void	builtins_error(char *s);

#endif
