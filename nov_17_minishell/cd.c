/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrsargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 03:04:56 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/11/18 03:05:01 by vrsargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	g_to_home(t_env **tab, char **rl)
{
	if (!rl[1])
		chdir(find_val_by_key(tab, "HOME"));
	else if (ft_strlen(rl[1]) > 2)
	{
		rl[1] += 2;
		chdir(find_val_by_key(tab, "HOME"));
		chdir(rl[1]);
	}
	else
		chdir(find_val_by_key(tab, "HOME"));
}

char	*find_val_by_key(t_env **tenv, char *key)
{
	t_env	*head;
	char	*res;

	res = "";
	head = *tenv;
	while (*tenv != NULL)
	{
		if (strcmp((*tenv)->key, key) == 0)
		{
			res = ft_strjoin(res, (*tenv)->value);
			return (res);
		}
		*tenv = (*tenv)->next;
	}
	*tenv = head;
	return (res);
}

void	change_val_by_key(t_env **tenv, char *key, char *val)
{
	t_env	*head;

	head = *tenv;
	while (*tenv != NULL)
	{
		if (strcmp((*tenv)->key, key) == 0)
		{
			(*tenv)->value = strdup(val);
			break ;
		}
		*tenv = (*tenv)->next;
	}
	*tenv = head;
}

void	cd(t_env **tenv, char **read_line)
{
	int				i;
	char			c[1024];

	getcwd(c, 1024);
	i = -1;
	printf(CYELLOW"%stestt!\n"GREEN, find_val_by_key(tenv, "HOME"));
	change_val_by_key(tenv, "OLDPWD", c);
	i = -1;
	if (read_line[1])
		while (*read_line[1] && *read_line[1] == 32)
			read_line++;
	if (!read_line[1] || *read_line[1] == '~' || *read_line[1] == '-')
	{
		g_to_home(tenv, read_line);
		return ;
	}
	else if (chdir(read_line[1]) == 0)
	{
		getcwd(c, 1024);
		change_val_by_key(tenv, "PWD", getcwd(c, 1024));
	}
	else
		printf(CYELLOW"no shuch a file or directory\n"GREEN);
}
