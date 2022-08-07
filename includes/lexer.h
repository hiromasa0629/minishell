/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:46:53 by hyap              #+#    #+#             */
/*   Updated: 2022/08/07 16:40:07 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "./clib.h"
# include "./utils.h"

void	split_pipe(t_data *data, char *line);
void	split_section(t_section **section);
void	expand_section(t_section **section, char **envp);
void	assign_types(t_list *ellst, t_element **el);
void	assign_redirect_type(t_element **el);
int		ft_has_prev_cmd(t_list *ellst);
int		ft_has_prev_arg(t_list *ellst);

/* Get strncmp 'n' while moving *env_var */
int		get_strncmp_n(char *env_var, int *i);

/* Main */
void	ft_lexer(t_data *data, char *line, char **envp);

#endif