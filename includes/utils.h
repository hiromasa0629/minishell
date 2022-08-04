/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:58:22 by hyap              #+#    #+#             */
/*   Updated: 2022/08/04 22:05:56 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "./clib.h"
# define PIPES_ERR -1
# define QUOTES_ERR -2
# define SCHAR_ERR -3
# define OP_ERR -4

/* Initially validate string */
int		is_valid_redirectop(char *s, int *i, int quote);
int		is_good(char *s);

/* Print error msg */
char	*error_msg(int err_code);
void	print_err(char *s, void (*prompt)(void));

/* Free */
void	free_all(t_data *data);

/* List utils */
t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstadd_back(t_list **lst, t_list *newlst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	print_ele_content(void *content);
void	print_sec_content(void *content);

/* Readline utils */
void	ft_add_history(char *s);
void	prompt_new_readline(void);
void	prompt_error_readline(void);

/* Utils */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isspace(char c);
int		ft_isquotes(char c);
int		ft_strlen(char *s);
char	ft_isredirectop(char c);
void	check_in_quotes(char c, int *quote);
int		has_redirectop(char *s);
int		ft_isalpha(char c);
int		ft_isnum(char c);
int		ft_issinglequote(char c);
int		ft_isexpandable(int quo, char *s, char first);
int		ft_has_envvar(char *s);


#endif