/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:38:11 by hyap              #+#    #+#             */
/*   Updated: 2022/08/11 13:16:16 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./clib.h"
# include "./utils.h"
# include "./lexer.h"
# include "./parser.h"
# include "./executors.h"
# include "./builtins.h"
# define TYPE_CMD 1
# define TYPE_FLAG 2
# define TYPE_ARG 3
# define TYPE_REDIRECT 4
# define TYPE_FILE 5
# define TYPE_DELIMITER 6
# define TYPE_EMPTY 7
# define T_SECTION 1
# define T_ELEMENT 2
# define RED_INPUT 1
# define RED_OUTPUT 2
# define RED_HEREDOC 3
# define MODE_APPEND 1
# define MODE_TRUNC 2
# define BLUE "\033[0;34m"
# define GREEN "\033[0;32m"
# define WHITE "\033[0;37m"
# define CYAN "\033[0;36m"

/* Execve return status */
int	status;

/*Signal handling*/
void	register_signal(void);
void	eof_exit(char *s);

#endif
