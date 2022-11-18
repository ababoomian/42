/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_nodes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrsargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 03:49:43 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/11/18 03:55:56 by vrsargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	print_nodes(t_nodes *head) {

	t_nodes	*current;
	int		i;

	current = head;
   	while (current != NULL) 
	{
		i = -1;
		printf("index : %d\n", current->index);
		while (current->heardock[++i])
	    	printf(CYELLOW"heredoc: %d : %s\n"GREEN, i, current->heardock[i]);
		i = -1;
		while (current->cmd[++i])
			printf(CYELLOW"cmd : %s\n"GREEN, current->cmd[i]);
		i = -1;
		while (current->infile[++i])
			printf(CYELLOW"inn: %s"GREEN, current->infile[i]);
        current = current->next;
    }
}

int	hd_count(char *str)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if ((str[i] == '<' && str[i + 1] == '<') && str[i + 1] != '\0')
		{
			i += 2;
			j += 2;
			while (str[i] != ' ' && str[i])
			{
				i++;
				j++;
			}
		}
		j++;
		i++;
	}
	return (j);
}

int		append_cnt(char *str)
{
	int		i;
	int		cnt;

	cnt = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
		{
			cnt++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		i++;
	}
	return (cnt);
}

int	infile_cnt(char *str)
{
	int		i;
	int		cnt;

	cnt = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] != '<' && str[i + 1])
			cnt++;
		else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			return (0);
		i++;
	}
	return (cnt);
}

int	outfile_cnt(char *str)
{
	int		i;
	int		cnt;

	cnt = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] != '>')
			cnt++;
		i++;
	}
	return (cnt);
}

char	*get_cleaned_str_meta(char *str)
{
	char	*res;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			i++;
		j++;
		i++;
	}
	i = 0;
	res = malloc(sizeof(char) * j + 1);
	j = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			while (str[i] != ' ' && str[i])
				i++;
		}
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

t_nodes	*new_nodes(int i, char **mx)
{
	t_nodes		*inited;
	char		*cmd;

	cmd = get_cleaned_str_meta(mx[i]);
	inited = NULL;
	inited = (t_nodes *)malloc(sizeof(t_nodes));
	if (inited == NULL)
		return (NULL);
	inited->heardock = heardock_init(mx[i]);
	inited->append = append_init(mx[i]);
	inited->infile = infile_init(mx[i]);
	inited->outfile = outfile_init(mx[i]);
	inited->cmd = ft_smart_split(cmd, 32);
	inited->index = i;
	free(cmd);
	inited->next = NULL;
	return (inited);
}

t_nodes	*init_nodes(char **mx)
{
	int			i;
	int			len;
	t_nodes 	*inited;
	t_nodes 	*tmp;

	inited = NULL;
	len = mat_len(mx);
	i = 0;
	inited = new_nodes(i, mx);
	tmp = inited;
	while (++i < len)
	{
		tmp->next = new_nodes(i, mx);
		tmp = tmp->next;
	}
	tmp = inited;
	return (inited);
}
