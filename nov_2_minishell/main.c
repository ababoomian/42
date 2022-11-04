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

void built_in(t_nodes *nds,char **read_lide,char **env,t_env **tenv)
{
	(void)nds;
	(void)env;
	int i = -1;
	if(nds->heardock)
		while(nds->heardock[++i])
			heredoc_redirect(nds->heardock[i]);
	if(!strcmp(read_lide[0],"pwd"))
	{
		char c[1024];
		getcwd(c,1024);
		printf("%s\n",c);
	}
	else if(strcmp(read_lide[0],"cd") == 0 )
		cd(tenv,read_lide);
	else if(strcmp(read_lide[0],"env") == 0)
		print_list_tenv(*tenv);
	else if(strcmp(read_lide[0],"exit") == 0)
		ft_exit(read_lide);
	else if(strcmp(read_lide[0],"echo") == 0)
		ft_echo(read_lide,*tenv);
	else if(strcmp(read_lide[0],"export") == 0)
		ft_main_export(tenv,read_lide);
	else if(strcmp(read_lide[0],"unset") == 0)
		 multi_unset(tenv,read_lide);
}

int if_built_in(char *str)
{
	if(!strcmp(str,"pwd") || !strcmp(str,"cd") || !strcmp(str,"echo") 
		|| !strcmp(str,"export") || !strcmp(str,"unset") || !strcmp(str,"env") || !strcmp(str,"exit") || !strcmp(str,APPEND) || !strcmp(str,INFILE) || !strcmp(str,OUTFILE) || !strcmp(str,"<<"))
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

char **find_path(t_env *tenv)
{
	char **res;
	res = NULL;
	while (tenv != NULL)
	{
		if(strcmp(tenv->key,"PATH") == 0)
		{
			res = ft_split(tenv->value,':');
			break;
		}
		tenv = tenv->next;
	}
	return(res);
	

}

char  *acc(char *cmd,t_env *tenv)
{
	int i;
	char *acc;
	char **path;

	i = -1;
	path = find_path(tenv);
	if(path == NULL)
		return(NULL);
	else if(cmd[0] == '/')
		return(cmd);
	while (path[++i])
	{
		acc = ft_strjoin(path[i],ft_strjoin("/",cmd));
		if(access(acc,(0)) == 0)
			return(acc);
		free(acc);
	}
	return(NULL);
}

void execution(t_nodes *nds,char **env, t_env *tenv)
{
	pid_t pid;
	char *cmd;
	cmd = NULL;
	(void)tenv;
			if(nds->cmd[0])
				cmd = acc(nds->cmd[0],tenv);
				if(cmd != NULL)
				{
					pid = fork();
					if (pid ==0)
					{
						if(nds->cmd[0])
							if(!if_built_in(nds->cmd[0]))
							{
								if(nds->cmd[0][0] == '/')
									execve(nds->cmd[0],nds->cmd,env);
								else
									execve(cmd,nds->cmd,env);
							}
						exit(1);
					}
					else
						wait(NULL);
				}
		 	if(nds->cmd[0])
				built_in(nds,nds->cmd,env,&tenv);
}

void handler(int sig)
{	
	(void)sig;
	return ;
}

int main(int ac,char **av,char **env)
{
    (void)av;
	(void)ac;
	t_env *tenv;
	t_nodes *nds;

	tenv = init_env_tenv(env);		
	printf(GREEN"wellcome to minishell\n");
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
		print_nodes(nds);
		while(nds!= NULL)
		{
			if(nds)
				execution(nds,env,tenv);
			nds = nds->next;
		}
	 }
    return (0);
}
