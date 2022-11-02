# include "./minishell.h"

void multi_unset(t_env **tenv,char **read_line)
{
	int i;
	i = 0;
	if(mat_len(read_line) == 1)
		return ;
	else if(mat_len(read_line) >= 2)
	{
		while(++i < mat_len(read_line))
			ft_unset(tenv,read_line[i]);
	}
}

int find_index(t_env **head,char *key)
{
	int res;

	res = 0;
	while ((*head) != NULL)
	{
		if(strcmp((*head)->key,key) == 0)
			return(res);
		res++;
		*head = (*head)->next;
	}
	return(-1);
}

void  ft_unset(t_env **head,char *key)
{
	int pos;
	int i;

	i = -1;

	pos = find_index(head,key);
	
	if(pos == -1)
		return ;
	(*head)->del = 1;
}