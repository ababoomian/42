# include "./minishell.h"

int ft_lst_size(t_env *tenv)
{
	int size;

	size = 0;
	while (tenv)
	{
		tenv = tenv->next;
		size++;
	}
	return(size);
}

char **list_to_env(t_env *tenv)
{
	int i;
	char **res;

	res = malloc(sizeof(char *) * ft_lst_size(tenv) + 1);
	i = 0;
	while (tenv)
	{
		if(tenv->del == 0)
		{
			res[i] = ft_strjoin(tenv->key,"=");
			res[i] = ft_strjoin(res[i],tenv->value);
			i++;
		}
		tenv = tenv->next;
	}
	return(res);
}