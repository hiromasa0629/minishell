/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clib.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:11:19 by hyap              #+#    #+#             */
/*   Updated: 2022/08/04 19:16:00 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIB_H
# define CLIB_H
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include "../readline-8.1/include/readline/history.h"
# include "../readline-8.1/include/readline/readline.h"

typedef struct s_data t_data;
typedef struct s_section t_section;
typedef struct s_element t_element;
typedef struct s_list t_list;

struct s_list {
	void	*content;
	t_list	*next;
	t_list	*prev;
};

struct s_data {
	int			sec_count;
	char		**envp;
	t_list		*seclst;
};

struct s_section {
	t_list		*ellst;
	char		*sec;
	int			numth;
	int			el_count;
};

struct s_element {
	char		*ele;
	int			type;
	int			numth;
	int			parent;
	int			is_good;
};

#endif