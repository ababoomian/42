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
	char *s;
	char *s1;
	s1 = "";
	s = "";
	//char *helper;

	res = malloc(sizeof(char *) * ft_lst_size(tenv) + 1);
	i = 0;
	while (tenv)
	{
		if(tenv->del == 0)
		{
			s = ft_strjoin(tenv->key,"=");
			res[i] = s;
			s1 = ft_strjoin(res[i],tenv->value);
			res[i] = s1;
			free(s);
			//free(s1);
			i++;
		}
		tenv = tenv->next;
	}
	return(res);
}