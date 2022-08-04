/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 17:18:04 by hyap              #+#    #+#             */
/*   Updated: 2022/08/04 22:06:27 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_env(char **envp, char **env_var)
{
	int		i;
	char	*path;
	char	*tmp;
	int		n;

	tmp = (*env_var);
	n = get_strncmp_n(env_var);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], tmp, n) == 0)
		{
			path = envp[i];
			while (*path != '=')
				path++;
			path++;
			return (path);
		}
		i++;
	}
	return (NULL);
}

int	total_new_element_length(char *ele, char **envp)
{
	char	*s;
	int		len;
	int		quote;

	s = ele;
	len = 0;
	quote = 0;
	while (*s)
	{
		if (ft_issinglequote(*s))
			check_in_quotes(*s, &quote);
		if (ft_isexpandable(quote, s, *ele))
		{
			s++;
			len += ft_strlen(find_env(envp, &s));
			if (*s == '$' && !(*s))
				continue ;
			printf("len: %d, *s: %c\n", len, *s);
		}
		else
		{
			len++;
			s++;
		}
	}
	return (len);
}

void	store_new_element(char **envp, char **tmp, char **new_ele, int *i)
{
	char	*target;

	(*tmp)++;
	target = find_env(envp, tmp);
	if (!target)
		return ;
	while (*target)
		(*new_ele)[(*i)++] = *(target)++;
}

void	expand_element(t_element **el, char **envp)
{
	int		len;
	char	*tmp;
	char	*new_ele;
	int		quote;
	int		i;

	tmp = (*el)->ele;
	len = total_new_element_length(tmp, envp);
	new_ele = (char *)malloc(sizeof(char) * (len + 1));
	printf("total size: %d\n", len + 1);
	new_ele[len] = '\0';
	quote = 0;
	i = 0;
	while (*tmp)
	{
		if (ft_issinglequote(*tmp))
			check_in_quotes(*tmp, &quote);
		if (ft_isexpandable(quote, tmp, *((*el)->ele)))
		{
			store_new_element(envp, &tmp, &new_ele, &i);
		}
		if (*tmp != '$')
			new_ele[i++] = *(tmp)++;
		tmp++;
	}
	free((*el)->ele);
	(*el)->ele = new_ele;
}

void	expand_section(t_section **section, char **envp)
{
	t_list		*ellst;
	t_element	*el;

	ellst = (*section)->ellst;
	while (ellst)
	{
		el = (t_element *)ellst->content;
		if (el->type != TYPE_DELIMITER && ft_has_envvar(el->ele))
			expand_element(&el, envp);
		ellst = ellst->next;
	}
}