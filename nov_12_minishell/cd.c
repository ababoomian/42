# include "./minishell.h"

void g_to_home(t_env **tab,char **rl)
{
	//printf("%stestt!\n",find_val_by_key(tab,"HOME"));
	//print_list_tenv(*tab);
	if(!rl[1])
		chdir(find_val_by_key(tab,"HOME"));
	else if(ft_strlen(rl[1]) > 2)
	{
		rl[1] += 2;
		chdir(find_val_by_key(tab,"HOME"));
		chdir(rl[1]);
	}
	else
		chdir(find_val_by_key(tab,"HOME"));
}

/*void to_home_env(t_table *tab,char **rl)
{
	int i;
	
	i = -1;
	while(tab->env[++i] && )
	{

	}
}
*/
/* char first_ch(char *str)
{
	int i;
	i = -1;
	while ( str[++i] && str[i] == 32);
	return (str[i]);
	
} */

char *find_val_by_key(t_env **tenv,char *key)
{
	t_env *head;
	char *res;
	
	res = "";
	head = *tenv;
	while (*tenv != NULL)
	{
		if (strcmp((*tenv)->key,key) == 0)
		{
			//printf("vallll%s",(*tenv)->value);
			res = ft_strjoin(res,(*tenv)->value);
			//ft_strlcpy(res,(*tenv)->value,ft_strlen((*tenv)->value));
			return(res);
		}
		*tenv = (*tenv)->next;
	}
	*tenv = head;
	return(res);
}

void change_val_by_key(t_env **tenv,char *key,char *val)
{
	//char *res;
	//res = NULL;
	t_env *head;

	head  = *tenv;
	while( *tenv != NULL)
	{
		if (strcmp((*tenv)->key,key) == 0)
		{
			(*tenv)->value = strdup(val);
			break ;
		}
		*tenv = (*tenv)->next;
	}
	*tenv = head;
}

void cd(t_env **tenv,char **read_line)
{
	int i;
	char c[1024];
	getcwd(c,1024);
	i = -1;
	printf(CYELLOW"%stestt!\n"GREEN,find_val_by_key(tenv,"HOME"));
	change_val_by_key(tenv,"OLDPWD",c);
	i = -1;
	if(read_line[1])
		while(*read_line[1] && *read_line[1] == 32)
			read_line++;
	if(!read_line[1] || *read_line[1] == '~' || *read_line[1] == '-')
	{
		g_to_home(tenv,read_line);
		return;
	}
	
	else if(chdir(read_line[1]) == 0)
	{
		getcwd(c,1024);
		change_val_by_key(tenv,"PWD",getcwd(c,1024));
	}
	else
		printf(CYELLOW"no shuch a file or directory\n"GREEN); 
	//free(c);
}