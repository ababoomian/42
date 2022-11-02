# include "./minishell.h"
//# include <stdio.h>


void print_list_tenv(t_env *head)
{

    t_env *current = head;
   	while ( current != NULL ) 
	{
		//printf("hello\n\n\n");
		if(current->del != 1)
        	printf("%s : %s \n", current->key,current->value);
        current = current->next;
    }
}

/* char *get_key_env(char *env)
{
	int	i;
	char *res;

	i = 0;
	while(env[i] != '=')
		i++;
	res = malloc(sizeof(char) * ft_strlen(env) + 1);
	if(!res)
		return NULL;
	i = 0;
	while(env[i] != '=')
	{
		res[i] = env[i];
		++i;
	}
	res[i] = '\0';
	return (res);
}
char	*get_value_env(char *env)
{
	int	i;
	int	j;
	char *res;

	i = 0;
	j = 0;
	while(env[i] != '=')
		i++;
	res = malloc(sizeof(char) * (ft_strlen(env) - i) + 1);
	i++;
	while(env[i])	
	{
		res[j] = env[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return res;

} */

t_env	*new_dict_tenv(char *key, char *value)
{
	t_env *new_t_env;

	new_t_env = (t_env*)malloc(sizeof(t_env));
	if(new_t_env == NULL)
		return (NULL);
	new_t_env->key = key;
	new_t_env->value =value;
	new_t_env->del = 0;
	new_t_env->next = NULL;	

	return(new_t_env);
}

t_env	*init_env_tenv(char **env)
{
	t_env *head;
	t_env *tmp;
	int i = 0;
	head = new_dict_tenv(get_key_env(env[i]),get_value_env(env[i]));
	tmp = head;
	while (env[++i])
	{
		tmp->next = new_dict_tenv(get_key_env(env[i]),get_value_env(env[i]));
		tmp = tmp->next;
	}
	return(head);
}