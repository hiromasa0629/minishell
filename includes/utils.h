/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:58:22 by hyap              #+#    #+#             */
/*   Updated: 2022/11/10 12:11:08 by hyap             ###   ########.fr       */
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
int		is_good(char *s, t_data *data);

/* Print error msg */
char	*error_msg(int err_code);
void	print_err(char *s, void (*prompt)(void));

/* Free */
void	free_all(t_data *data);
void	free_execve(t_exec *exec);

/* List utils */
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstadd_back(t_list **lst, t_list *newlst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	print_ele_content(void *content);
void	print_sec_content(void *content);
void	del_el(void *content);

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
int		ft_isexpandable(int quo, char *s, int i);
int		ft_has_envvar(char *s);
int		ft_has_quotes(char *s);
int		ft_iscomplete_op(char *s);
int		ft_hasslash(char *s);
int		ft_isimplemented(t_list *ellst);
int		ft_isrunbuiltins(t_element *el);
char	**ft_split(char *s, char c);
char	*concat_two_string(char *one, char *two);
char	*ft_itoa(int n);
int		ft_numlen(long long n);
int		ft_cmd_exist(t_list *ellst);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	ft_putstr_fd(int fd, char *s);
int		ft_atoi(const char *s);
void	exit_error(t_data *data, int err);
int		ft_has_special_unset(char *s);
int		ft_has_special_export(char *s);
int		ft_strcmp(const char *s1, const char *s2);
void	free_splits(char **splits);

#endif
