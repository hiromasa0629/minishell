/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:38:11 by hyap              #+#    #+#             */
/*   Updated: 2022/08/04 17:00:06 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./clib.h"
# include "./utils.h"
# include "./lexer.h"
# include "./parser.h"
# define TYPE_CMD 1
# define TYPE_FLAG 2
# define TYPE_ARG 3
# define TYPE_REDIRECT 4
# define TYPE_FILE 5
# define TYPE_DELIMITER 6
# define T_SECTION 1
# define T_ELEMENT 2
# define BLUE "\033[0;34m"
# define GREEN "\033[0;32m"
# define WHITE "\033[0;37m"

/*Signal handling*/
void	register_signal(void);
void	eof_exit(char *s);

#endif
