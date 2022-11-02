# include "./minishell.h"
//# include <stdio.h>


void print_list(t_dict *head) {

    t_dict *current = head;
   	while ( current != NULL ) 
	{
		//printf("hello\n\n\n");
        printf("%s : %s \n", current->key,current->value);
        current = current->next;
    }
}


/* int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}
 */
char *get_key_env(char *env)
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


}

// void	push_new_t_dict(t_dict **head)
// {
// 	t_dict *new_t_dict;
// 	new_t_dict = (t_dict*)malloc(sizeof(t_dict));
// 	new_t_dict = *head;
// 	while(new_t_dict != NULL)
// 		new_t_dict = new_t_dict->next;
// 	new_t_dict->next = NULL;
	
// }

t_dict	*new_dict(char *key, char *value)
{
	t_dict *new_t_dict;

	new_t_dict = (t_dict*)malloc(sizeof(t_dict));
	if(new_t_dict == NULL)
	{
		printf("\nout of memory\n");
		return (NULL);
	}
	new_t_dict->key = key;
	new_t_dict->value =value;
	new_t_dict->next = NULL;
	return(new_t_dict);
}

t_dict	*init_dict(char **env)
{
	t_dict *head;
	t_dict *tmp;
	int i = 0;

	head = new_dict(get_key_env(env[i]),get_value_env(env[i]));
	tmp = head;
	while (env[++i])
	{
		tmp->next = new_dict(get_key_env(env[i]),get_value_env(env[i]));
		tmp = tmp->next;
	}
	return(head);
}
