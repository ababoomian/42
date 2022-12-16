/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_nodes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 03:49:43 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/12/05 22:01:18 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./minishell.h"

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
			printf(CYELLOW"inn: %s\n"GREEN, current->infile[i]);
		i = -1;
		while (current->append[++i])
			printf(CYELLOW"append: %s\n"GREEN, current->append[i]);
		i = -1;
		while (current->outfile[++i])
			printf(CYELLOW"outfile: %s\n"GREEN, current->outfile[i]);
		i = -1;
		while (current->redir[++i])
			printf(UMAG"redir: %s\n"GREEN, current->redir[i]);
		printf(RESET"read _line %s \n"GREEN,current->rd_line);
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
				i++;
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
		if(str[i] == '\'')
		{
			while(str[i] && str[i] != '\'')
				i++;
			i++;
		}
		if(str[i] == '\"')
		{
			while(str[i] && str[i] != '\"')
				i++;
			i++;
		}
		if (str[i] && (str[i] == '<' || str[i] == '>'))
		{
			while (str[i] && str[i] != ' ' && !is_meta(str[i]))
				i++;
		}
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

char **cmd_init(char *str)
{
	char **cpy;
	char **res;
	char *test;
	int i;
	int del;

	i = -1;
	del = 0;
	test = "";
	res = NULL;
	cpy= ft_smart_split(str,' ');
	res = malloc(sizeof(char *) * mat_len(cpy) + 1);
	
	while(cpy[++i])
	{
		if(cpy[i][0] == '\'' || cpy[i][0] == '\"')
		{
			res[i] = ft_strdup(cpy[i]);
			//res[i] = ft_strjoin(cpy[i]," ");
		}
		else
			res[i] = ft_strjoin("",cpy[i]);
		//res[i] = ft_strjoin(res[i]," ");
	}
	i = -1;
	while(res[++i])
		test = ft_strjoin(test,res[i]);
	return(res);


}

char *lexer(t_nodes *nds,char *str)
{
	int i;
	int j;
	char **sp;
	char *res;

	res = "";
	(void)nds;
	sp = ft_smart_split(str, ' ');
	i = -1;
	j = 0;
	while (sp[++i])
	{
		if(sp[i][0] == '\'' || sp[i][0] == '\"')
		{
			res = ft_strjoin(res,sp[i]);
			res = ft_strjoin(res," ");
		}
		else if(strcmp(sp[i],">>") == 0 || strcmp(sp[i],"<<") == 0 || strcmp(sp[i],">") == 0 || strcmp(sp[i],"<") == 0 )
		{
			res = ft_strjoin(res,sp[i]);\
			if(sp[i + 1])
				res = ft_strjoin(res,sp[i + 1]);
			res = ft_strjoin(res," ");
			i++;
		}
		else
		{
			if(sp[i])
			{
				res = ft_strjoin(res,sp[i]);
				res = ft_strjoin(res," ");
			}
		}
	}
	
	return(res);
	
}
char **parse_cmd(char **str)
{
	int i;
	char *res;

	i = -1;
	res = "";
	while (str[++i])
	{
		if(str[i] && ((str[i][0] == '\'' || str[i][0] == '\"') || (str[i][0] != '<' && str[i][0] != '>')))
		{
			res = ft_strjoin(res,str[i]);
			res = ft_strjoin(res," ");
		}
	}
	return(ft_smart_split(res,' '));
}

t_nodes	*new_nodes(int i, char **mx)
{
	t_nodes		*inited;
	char		*cmd;
	char		*test;

	cmd = get_cleaned_str_meta(mx[i]);
	//cmd = "";
	inited = NULL;
	inited = (t_nodes *)malloc(sizeof(t_nodes));
	//printf(UBLU"%s\n"GREEN,lexer(inited,mx[i]));
	test = lexer(inited,mx[i]);
	if (inited == NULL)
		return (NULL);
	inited->heardock =heardock_init(test);
	inited->append = append_init(test);
	inited->infile = infile_init(test);
	inited->outfile = outfile_init(test);
	inited->cmd = parse_cmd(ft_smart_split(test,32));
	inited->redir = init_redir(test);
	inited->index = i;
	//free(cmd);
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
