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
		if(current->heardock)
			while (current->heardock[++i])
	    		printf(CYELLOW"heredoc: %d : %s\n"GREEN, i, current->heardock[i]);
		i = -1;
	if(current->cmd)
		while (current->cmd[++i])
			printf(CYELLOW"cmd : %s\n"GREEN, current->cmd[i]);
		i = -1;
	if(current->infile)
		while (current->infile[++i])
			printf(CYELLOW"inn: %s\n"GREEN, current->infile[i]);
		i = -1;
	if(current->append)
		while (current->append[++i])
			printf(CYELLOW"append: %s\n"GREEN, current->append[i]);
		i = -1;
	if(current->outfile)
		while (current->outfile[++i])
			printf(CYELLOW"outfile: %s\n"GREEN, current->outfile[i]);
		i = -1;
	if(current->redir)
		while (current->redir[++i])
			printf(UMAG"redir: %s\n"GREEN, current->redir[i]);
		printf(RESET"read _line %s \n"GREEN,current->rd_line);
		printf("okk\n");
	if(current->tok)
		print_tok(current);
        current = current->next;

    }
}

int last_input_redir_index(t_token *snoop_dog)
{
	while (snoop_dog->next != NULL)
		snoop_dog = snoop_dog->next;
	while (snoop_dog != NULL)
	{
		//if(snoop_dog && snoop_dog->prev)
			snoop_dog = snoop_dog->prev;
		if(snoop_dog && (snoop_dog->type == _HEREDOC || snoop_dog->type == _RED_IN))
			return(snoop_dog->index);
	}
	return(-2);
}
int last_output_redir_index(t_token *snoop_dog)
{
	while (snoop_dog->next != NULL)
		snoop_dog = snoop_dog->next;
	
	while (snoop_dog != NULL)
	{
		//if(snoop_dog && snoop_dog->prev)
			snoop_dog = snoop_dog->prev;
		if(snoop_dog && (snoop_dog->type == _APPEND || snoop_dog->type == _RED_OUT))
			return(snoop_dog->index);
	}
	return(-2);
}

t_nodes	*new_nodes(int i,char *mx)
{
	t_nodes		*inited;
	t_token		*tok;

	tok = NULL;
	inited = NULL;
	inited = (t_nodes *)malloc(sizeof(t_nodes));
	if (inited == NULL)
		return (NULL);
	set_token(&mx,&tok);
	inited->tok = malloc(sizeof(t_token));
	inited->tok = tok;
	//inited->next->tok = NULL;
	inited->last_in_red = last_input_redir_index(inited->tok);
	inited -> last_out_red = last_output_redir_index(inited->tok);
	inited->index = i;
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
	inited = new_nodes(i,mx[0]);
	tmp = inited;
	while (++i < len)
	{
		tmp->next = new_nodes(i,mx[i]);
		tmp = tmp->next;
	}
	free(mx);
	tmp = inited;
	return (inited);
}
