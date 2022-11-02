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

void built_in(char **read_lide,char **env,t_table *tab, t_env **tenv)
{
	//char c[1024] ;
	//c = getcwd(NULL,0);
	(void)env;
	if(!strcmp(read_lide[0],"pwd"))
	{
		char c[1024];
		getcwd(c,1024);
		printf("%s\n",c);
	}
	else if(strcmp(read_lide[0],"cd") == 0 )
		cd(tab,read_lide);
	else if(strcmp(read_lide[0],"env") == 0)
		print_list_tenv(*tenv);
	else if(strcmp(read_lide[0],"exit") == 0)
		ft_exit(read_lide);
	else if(strcmp(read_lide[0],"echo") == 0)
		ft_echo(read_lide,tab);
	else if(strcmp(read_lide[0],"export") == 0)
		ft_main_export(tenv,read_lide);
	else if(strcmp(read_lide[0],"unset") == 0)
		 multi_unset(tenv,read_lide);
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
	//tab->path = "sss";
	tab->env = env;
	while (env[i])
	{
		if(strncmp("PATH=",env[i],5) == 0)
		{
			env[i] += 5;
			tab->path = ft_split(env[i],':');
		}
		if(strncmp("PWD=",env[i],4) == 0)
			tab->pwd = env[i];
		i++;
	}
	i = -1;
	//while(tab->path[++i])
		//tab->path[i] = ft_strjoin(tab->path[i],"/");
	return(tab);

}

int acc(t_table *tab,char *test)
{
	int i;
	char *acc;

	i = -1;
	while (tab->path[++i])
	{
		acc = ft_strjoin(tab->path[i],test);
		if(access(acc,(0)) == 0)
		{
			free(acc);
			return(i);
		}
		free(acc);
	}
	return(-1);
}

void execution(t_table *tab,char *line,char **env, t_env *tenv)
{
	int i;
	pid_t pid;

	i = -1;
	tab->cmd = ft_split(line,' ');
			if(*tab->cmd)
				tab->test = ft_strjoin("/",tab->cmd[0]); 
			if(tab->test)
				i = acc(tab,tab->test);
				if(i != -1)
				{
					pid = fork();
					if (pid ==0)
					{
						if(tab->test)
							if(!if_built_in(tab->cmd[0]))
								execve(ft_strjoin(tab ->path[i],tab->test),tab->cmd,env);
						exit(1);
					}
					else
						wait(NULL);
				}
			if(tab->cmd[0])
				built_in(tab->cmd,env,tab,&tenv);
		i = -1;
		 while(tab->cmd[++i])
			free(tab->cmd[i]);
		free(tab->cmd);
		i = -1;
		//while(tab->path[++i])
			//free(tab->path[i]);
		//free(tab->path);
		if(*tab->cmd)
			free(tab->test);
		free(line);
}

void handler(int sig)
{	
	(void)sig;
	return ;
}

int main(int ac,char **av,char **env)
{
	
	
	int i;
    (void)av;
	(void)ac;
	(void)env;
	t_table *tab;
	t_env *tenv;
	t_dict *dict;
	t_nodes *nds;
		tenv = init_env_tenv(env);
		dict = init_dict(env);
		tab = create_table(env);
		printf(GREEN"wellcome to minishell\n");
	//	signal(SIGINT,handler);
	//	signal(SIGQUIT,handler);	
	while(1)
	 {	
		char	*line = readline("😎minishell->");
		if (!line)
			exit (1);
		if (line[0])
			add_history(line);
		else
			continue;
		char **pipes = ft_split(line,'|');
		nds = init_nodes(pipes);
		//print_nodes(nds);
		i = -1;
		 while(pipes[++i])
			execution(tab,pipes[i],env,tenv);
		free(pipes);
		if(line)
			free(line);
		i = -1;
		while (nds->heardock[++i])
			free(nds->heardock[i]);
		free(nds->heardock);
		free(nds);
	 }
    return (0);
}
