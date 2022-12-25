# include "./minishell.h"

void remove_space(t_nodes *addres)
{
	t_token	*ptr;
	t_token	*tmp;
	int		index;
	
	tmp = addres->tok;
	ptr = addres->tok;
	while (tmp)
	{
		if (tmp && tmp->type == _SPACE)
		{
			if(tmp->next && is_redirection(tmp->next->type))
			{

				index = tmp->index;
				tmp = tmp->next;
				remove_node_from_token(&(addres->tok), index);
			}
			else
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}

void change_type(t_token **nds,int index)
{
	t_token	*tmp;

	tmp = *nds;
	while (tmp && tmp->index != index)
		tmp = tmp->next;
	if(tmp && tmp->index == index)
		tmp->type = -1;

}

void change_type_2(t_nodes **nds,int index)
{
	t_nodes	*tmp;

	tmp = *nds;
	while (tmp && tmp->tok->index != index)
		tmp = tmp->next;
	if(tmp && tmp->tok->index == index)
		tmp->tok->type = -1;
}


int heredoc(t_token **addres,int last_in_red)
{
	t_token	*ptr;
	t_token	**tmp;
	int		simp;
	int		index;
	
	tmp = addres;
	ptr = *tmp;
	//ptr = addres->tok;
	printf("\n\n%p %p\n\n", *addres,tmp);
	while (tmp)
	{
		if (tmp && (*tmp)->type == _HEREDOC)
		{
			simp = 0;
			index = (*tmp)->index;
			if(last_in_red == index)
				simp = 1;	
			*tmp = (*tmp)->next;
			change_type(&ptr,index);
			//remove_node_from_token(&(addres->tok), index);
			//run_heredoc(addres, tmp->token, tmp->type);
			printf("dell :%s\n",(*tmp)->token);
			if(simp == 1)
				heredoc_redirect((*tmp)->token);
			else
				heredoc_no_redirect((*tmp)->token);
			index = (*tmp)->index;
			*tmp = (*tmp)->next;
			//remove_node_from_token(&(addres->tok), index);
			change_type(addres,index);
		}
		else
			*tmp = (*tmp)->next;
	}
	*tmp = ptr;
	return (0);
}

void	output_no_redirect(char *file)
{
	int fd;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(fd);

}

void output_redirect(char *file)
{
	int fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 1);
	//close(fd);
}

int output(t_nodes *addres)
{
	t_token	*ptr;
	t_token	*tmp;
	int		simp;
	int		index;
	
	tmp = addres->tok;
	ptr = addres->tok;
	while (tmp)
	{
		if (tmp && tmp->type == _RED_OUT)
		{
			simp = 0;
			index = tmp->index;
			if(addres->last_out_red == index)
				simp = 1;	
			tmp = tmp->next;
			change_type(&(addres->tok),index);
			//remove_node_from_token(&(addres->tok), index);
			//run_heredoc(addres, tmp->token, tmp->type);
			printf("dell :%s\n",tmp->token);
			if(simp == 1)
				output_redirect(tmp->token);
			else
				output_no_redirect(tmp->token);
			index = tmp->index;
			tmp = tmp->next;
			//remove_node_from_token(&(addres->tok), index);
			change_type(&(addres->tok),index);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

void	input_no_redirection(char *file)
{
	int fd;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		return ;
	}
	close(fd);
}

void	input_redirect(char *file)
{
	int		fd;
	char	*s;

	s = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return ;
	dup2(fd, 0);
	s = gnl(fd);
	write(fd, s, ft_strlen(s));
	close(fd);
	free(s);
}

int input(t_nodes *addres)
{
	t_token	*ptr;
	t_token	*tmp;
	int		simp;
	int		index;
	
	tmp = addres->tok;
	ptr = addres->tok;
	while (tmp)
	{
		if (tmp && tmp->type == _RED_IN)
		{
			simp = 0;
			index = tmp->index;
			if(addres->last_in_red == index)
				simp = 1;	
			tmp = tmp->next;
			change_type(&(addres->tok),index);
			//remove_node_from_token(&(addres->tok), index);
			//run_heredoc(addres, tmp->token, tmp->type);
			printf("dell :%s\n",tmp->token);
			if(simp == 1)
				input_no_redirection(tmp->token);
			else
				input_redirect(tmp->token);
			index = tmp->index;
			tmp = tmp->next;
			//remove_node_from_token(&(addres->tok), index);
			change_type(&(addres->tok),index);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

void append_no_redirect(char *file)
{
	int fd;

	fd = open(file, O_CREAT |   O_APPEND | O_WRONLY , 0644);
	close(fd);
}

/* void	append_redirect(char *file)
{
	int fd;

	fd = open(file, O_CREAT |   O_APPEND | O_WRONLY , 0644);
	dup2(fd, 1);
	close(fd);
} */

void	append_redirect(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND, 0644);
	if (fd > 0)
	{
		dup2(fd, 1);
		write(fd, "\n", 1);
		close(fd);
	}
	else
	{
		write(2, "no such a file or directory\n", 29);
		return ;
	}
	return ;
} 

int append(t_nodes *addres)
{
	t_token	*tmp;
	int		simp;
	int		index;
	
	tmp = addres->tok;
	while (tmp)
	{
		if (tmp && tmp->type == _APPEND)
		{
			simp = 0;
			index = tmp->index;
			if(addres->last_in_red == index)
				simp = 1;	
			tmp = tmp->next;
			change_type(&(addres->tok),index);
			if(simp == 1)
				append_no_redirect(tmp->token);
			else
				append_redirect(tmp->token);
			index = tmp->index;
			tmp = tmp->next;
			change_type(&(addres->tok),index);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}