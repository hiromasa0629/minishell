/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:46:53 by hyap              #+#    #+#             */
/*   Updated: 2022/08/04 16:20:31 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "./clib.h"
# include "./utils.h"

void	split_pipe(t_data *data, char *line);
void	split_section(t_section **section);
void	complete_element(t_section **section);

/* Main */
void	ft_lexer(t_data *data, char *line);

#endif