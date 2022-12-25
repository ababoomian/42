#include "./minishell.h"

int redirection_size(t_token *tok,int type)
{
	int res;
	res = 0;
	while (tok != NULL)
	{
		if(tok->type == type)
			res++;
		tok = tok->next;
	}
	return(res);
}

char **heredoc_fill(t_token *tok)
{
	int i;
	char **res;
	int len;
	len = redirection_size(tok,8);
	i = 0;
	res = NULL;
	if(len == 0)
		return(NULL);
	res = malloc(sizeof(char *) * len + 1);
	if(!res)
		return(NULL);
	while (tok != NULL)
	{
		if(tok->type == _HEREDOC)
		{
			res[i] = ft_strdup(tok->next->token);
			i++;
		}
		tok = tok->next;
	}
	res[i] = 0;
	return(res);
}

int is_redirection(int type)
{
	return(type == 3 || type == 2 || type == 8 || type == 9);
}

int cmd_size(t_token *tok)
{
	int res;
	res = 0;
	while (tok != NULL)
	{
		if(tok && tok->type != -1 && tok->type != 1)
			res++;
		tok = tok->next;
	}
	return(res);
}

char **fill_cmd(t_token *tok)
{
	int len;
	char **res;
	int i;

	i = -1;
	res = NULL;
	len = cmd_size(tok);
	printf(" len : %d\n",len);
	if(len == 0)
		return(NULL);
	res = malloc(sizeof(char *) * len + 1);
	if(!res)
		return(NULL);
	while (tok != NULL)
	{
		if(tok && tok->type != -1 && tok->type != 1)
			res[++i] = ft_strdup(tok->token);
		tok = tok->next;
	}
	res[++i] = 0;
	return(res);
}

void remove_hrd(t_token **tok)
{
	int len;
	t_token *tmp;
	
	tmp = *tok;
	len = redirection_size(*tok,8);
	if(len == 0)
		return ;
	while (*tok != NULL)
	{
		if ((*tok)->type == 8)
		{
			*tok = (*tok)->next;
			remove_node_from_token(tok,(*tok)->prev->index);
			*tok = (*tok)->next;
			remove_node_from_token(tok,(*tok)->prev->index);
		}
		if((*tok)->next)
			*tok = (*tok)->next;
		else
			return ;
	}
	*tok = tmp;
}