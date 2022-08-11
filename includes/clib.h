/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clib.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:11:19 by hyap              #+#    #+#             */
/*   Updated: 2022/08/11 20:50:19 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIB_H
# define CLIB_H
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <termios.h>
# include "../readline-8.1/include/readline/history.h"
# include "../readline-8.1/include/readline/readline.h"

typedef struct s_data t_data;
typedef struct s_section t_section;
typedef struct s_element t_element;
typedef struct s_list t_list;
typedef struct s_helper t_helper;
typedef struct s_exec t_exec;
typedef struct stat t_stat;
typedef struct termios t_termios;
typedef struct s_cmd t_cmd;

struct s_list {
	void	*content;
	t_list	*next;
	t_list	*prev;
};

struct s_data {
	int			sec_count;
	char		**envp;
	int			env_edited;
	t_list		*seclst;
	int			pipein;
	int			pipeout;
	int			tmpstdout;
	int			tmpstdin;
};

struct s_section {
	t_list		*ellst;
	t_list		*host;
	char		*sec;
	int			numth;
	int			el_count;
};

struct s_element {
	char		*ele;
	int			type;
	int			numth;
	int			parent;
	t_list		*host;
	int			is_good;
	int			is_expanded;
	int			is_absolute;
	int			red_type;
	int			red_mode;
};

struct s_helper {
	int		i;
	int		j;
	int		k;
	int		condone;
	int		condtwo;
	int		fd[2];
	int		pid;
	int		quote;
	int		len;
	int		lentwo;
	int		filein;
	int		fileout;
	int		tmpfilein;
	int		tmpfileout;
	char	*line;
	char	*linetwo;
	char	*linethree;
	char	**dptr;
	t_list	*tmplst;
};

struct s_exec {
	char	*b_path;
	char	**args;
};

struct s_cmd {
	char	*s;
	int		type;
};

#endif