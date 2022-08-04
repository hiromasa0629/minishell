/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:59:07 by hyap              #+#    #+#             */
/*   Updated: 2022/08/04 21:24:13 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEH_H
# define PARSEH_H
# include "./clib.h"
# include "./utils.h"

/* Get strncmp 'n' while moving *env_var */
int		get_strncmp_n(char **env_var);

void	expand_section(t_section **section, char **envp);

/* Main */
void	ft_parser(t_data *data);

#endif
