# include "minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

void ft_getenv(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n",env[i]);
	
}

void cd(t_table *tab,char **read_line)
{
	int i;

	i = -1;
	while (tab->env[++i])
		if(!strncmp(tab->env[i],"OLDPWD=",7))
			tab->env[i] = ft_strjoin("OLDPWD=",getcwd(NULL,200)); 
	i = -1;
	if(chdir(read_line[1]) == 0)
	{
		while (tab->env[++i])
			if(!strncmp(tab->env[i],"PWD=",4))
				tab->env[i] = ft_strjoin("PWD=",getcwd(NULL,200));
	}
	else
		printf("no shuch a file or directory\n"); 

}

int is_digit(char *str)
{
	int i;

	i = -1;
	while(str[++i])
		if(str[i] < '0' && str[i] > '9')
			return(0);
	return(1);		
}

void ft_exit(char **read_line)
{
	if(!read_line[1])
		exit(0);
	if(!is_digit(read_line[1]))
	{
		printf("exit\narguments must be numericcc ay eshh!!\n");
		return ;
	}
	else if(read_line[2])
	{
		printf("too many argument debilll!!\n");
		return ;
	}
	else
		exit(0);
}

void built_in(char **read_lide,char **env,t_table *tab)
{
	(void)env;
	(void)tab;
	if(!strcmp(read_lide[0],"pwd"))
		printf("%s\n",getcwd(NULL,100));
	else if(!strcmp(read_lide[0],"cd"))
		cd(tab,read_lide);
	else if(!strcmp(read_lide[0],"env"))
		ft_getenv(env);
	else if(!strcmp(read_lide[0],"exit"))
		ft_exit(read_lide);

}

int if_built_in(char *str)
{
	if(!strcmp(str,"pwd") || !strcmp(str,"cd") || !strcmp(str,"echo") 
		|| !strcmp(str,"export") || !strcmp(str,"unset") || !strcmp(str,"env") || !strcmp(str,"exit") )
			return(1);
	else
		return(0);
}

t_table *create_table(char **env)
{
	t_table *tab;
	int i;

	i = 0;
	tab = malloc(sizeof(t_table));
	tab->path = "sss";
	tab->env = env;
	while (env[i])
	{
		if(strncmp("PATH=",env[i],5) == 0)
			tab->path = env[i];
		if(strncmp("PWD=",env[i],4) == 0)
			tab->pwd = env[i];
		i++;
	}
	return(tab);

}

int main(int ac,char **av,char **env)
{
	  int i;
     (void)av;
	 (void)ac;
	 t_table *tab;

	 tab = create_table(env);
	 while(1)
	 {		
			char	*line = readline("minishell->");
			if (!line)
				exit (1);
			if (line[0])
				add_history(line);
			char **read_line = ft_split(line,' ');
			char **path = ft_split(tab->path,':');
			char *test;
			test = NULL;
			if(*read_line)
				test = ft_strjoin("/",read_line[0]);
			i = -1;
 			while(path[++i])
			{
				pid_t pid = fork();
				if (pid ==0)
				{
					if(test)
					{
						if(!if_built_in(read_line[0]))
							execve(ft_strjoin(path[i],test),read_line,env);			
					}
					exit(1);
				}
				else
					wait(NULL);
			} 
			if(read_line[0])
				built_in(read_line,env,tab);
	 }
    return (0);
}
