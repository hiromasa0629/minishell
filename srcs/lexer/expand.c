/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:18:04 by hyap              #+#    #+#             */
/*   Updated: 2022/08/11 15:07:46 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/***************************************
*	i: iterate envp 
*	j: ft_strncmp 'n'
*	k: retain the initial (*i)
****************************************/
char *find_env(char **envp, char *s, int *i)
{
	t_helper	h;
	char		*path;

	h.i = 0;
	if (s[*i] == '$')
		(*i)++;
	h.k = *i;
	h.j = get_strncmp_n(s, i);
	while (envp[h.i])
	{
		if (ft_strncmp(envp[h.i], &s[h.k], h.j) == 0)
		{
			path = envp[h.i];
			while (*path != '=')
				path++;
			path++;
			return (path);
		}
		h.i++;
	}
	return (NULL);
}

/***************************************
 *	*s 		element string
 *	**envp	envp
 *	
 *	i: 		iterate s
 *	quote	check closing quote
 *	len: 	return value
****************************************/
int	total_new_element_length(char *s, char **envp)
{
	t_helper	h;

	h.i = 0;
	h.quote = 0;
	h.len = 0;
	while (s[h.i])
	{
		if(ft_isquotes(s[h.i]))
			check_in_quotes(s[h.i], &(h.quote));
		if (ft_isexpandable(h.quote, s, h.i))
		{
			if (s[h.i + 1] == '?')
				h.len += ft_strlen(ft_itoa(status));
			else
				h.len += ft_strlen(find_env(envp, s, &h.i));
		}
		else
		{
			h.len++;
			h.i++;
		}
		if (s[h.i] == '$' && s[h.i + 1] == '?')
			h.i = h.i + 2;
	}
	return (h.len);
}

/***************************************
 *	**envp		envp
 *	**new_ele	new malloced element
 *	*s 			element string
 *	*i			current i position of elemet string
 *	*j			current j position of new malloced element
 *	
 *	line:		targetted env value
****************************************/
void	store_new_ele(char **envp, char **new_ele, char *s, int *i, int *j)
{
	t_helper	h;

	if (s[*i] == '$' && s[*i + 1] == '?')
	{
		h.i = 0;
		h.line = ft_itoa(status);
		while ((h.line)[h.i])
			(*new_ele)[(*j)++] = (h.line)[h.i++];
		free(h.line);
		*i = *i + 2;
	}
	else
	{	
		h.line = find_env(envp, s, i);
		if (!(h.line))
			return ;
		while (*(h.line))
			(*new_ele)[(*j)++] = *(h.line)++;
	}
}

/***************************************
 *	**el 	current element
 *	**envp	envp
 *	
 *	i: 		iterate (*el)->ele
 *	j:		iterate new malloced element
 *	line: 	(*el)->ele
 *	linetwo	newly malloced element
****************************************/
void	expand_element(t_element **el, char **envp)
{
	t_helper	h;

	h.quote = 0;
	h.i = 0;
	h.j = 0;
	h.line = (*el)->ele;
	h.len = total_new_element_length(h.line, envp);
	// printf("len: %d\n", h.len + 1);
	h.linetwo = (char *)malloc(sizeof(char) * (h.len + 1));
	(h.linetwo)[h.len] = '\0';
	while ((h.line)[h.i])
	{
		if (ft_isquotes((h.line)[h.i]))
		{
			check_in_quotes((h.line)[h.i], &(h.quote));
			// if (ft_issinglequote((char)(h.quote)));
		}
		if (ft_isexpandable(h.quote, h.line, h.i))
		{
			// printf("h.quote: %d\n", h.quote);
			store_new_ele(envp, &h.linetwo, h.line, &h.i, &h.j);
		}
		else
			(h.linetwo)[h.j++] = (h.line)[h.i++];
	}
	free((*el)->ele);
	(*el)->ele = h.linetwo;
	(*el)->is_expanded = 1;
}

void	expand_section(t_section **section, char **envp)
{
	t_list		*ellst;
	t_element	*el;
	t_element	*p_el;

	ellst = (*section)->ellst;
	while (ellst)
	{
		el = (t_element *)ellst->content;
		if (!ellst->prev && ft_has_envvar(el->ele))
			expand_element(&el, envp);
		else if (ellst->prev && ft_has_envvar(el->ele))
		{
			p_el = (t_element *)ellst->prev->content; 
			if (ft_strncmp(p_el->ele, "<<", 2) != 0)
				expand_element(&el, envp);
		}		
		ellst = ellst->next;
	}
}