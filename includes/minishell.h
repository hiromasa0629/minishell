/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:38:11 by hyap              #+#    #+#             */
/*   Updated: 2022/08/03 16:29:40 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include "../readline-8.1/include/readline/history.h"
# include "../readline-8.1/include/readline/readline.h"
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
# define PIPES_ERR -1
# define QUOTES_ERR -2
# define SCHAR_ERR -3
# define OP_ERR -4

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
};

/*Signal handling*/
void	register_signal(void);
void	eof_exit(char *s);

/*readline utils*/
void	prompt_new_readline(void);
void	my_add_history(char *s);
void	prompt_error_readline(void);

/*list utils*/
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *newlst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	print_ele_content(void *content);
void	print_sec_content(void *content);

/*free utils*/
void	free_all(t_data *data);

void	split_pipe(t_data *data, char *line);
void	split_section(t_section **section);

/*error management*/
void	print_err(char *s, void (*prompt)(void));
int		is_good(char *s);
char	*error_msg(int err_code);
int		is_valid_redirectop(char *s, int *i, int quote);

char	**ft_split(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isspace(char c);
int		ft_isquotes(char c);
void	check_valid_quotes(char *s);
char	*store_quotes_string(char **s);
void	del(void *content, int type);
int		ft_strlen(char *s);
void	check_in_quotes(char c, int *quote);
char	ft_isredirectop(char c);
int		has_redirectop(char *s);

#endif
