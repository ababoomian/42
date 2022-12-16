/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 04:05:26 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/12/08 23:20:02 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
# include "./minishell.h"

char	**find_path(t_env *tenv)
{
	char	**res;

	res = NULL;
	while (tenv != NULL)
	{
		if (strcmp(tenv->key, "PATH") == 0)
		{
			res = ft_split(tenv->value, ':');
			break ;
		}
		tenv = tenv->next;
	}
	return (res);
}

char	*acc(char *cmd, t_env *tenv)
{
	int			i;
	char		*acc;
	char		**path;
	char *s;
	char *s1;

	i = -1;
	s= "";
	s1= "";
	path = find_path(tenv);
	if (access(cmd, 0) == 0)
			return (cmd);
	if (path == NULL)
		return (NULL);
	else if (cmd[0] == '/')
		return (cmd);
	while (path[++i])
	{
		s = ft_strjoin("/", cmd);
		s1 =  ft_strjoin(path[i], s);
		acc = s1;
		//free(s1);
		free(s);
		if (access(acc, 0) == 0)
		{
			i = -1;
			while (path[++i])
				free(path[i]);
			free(path);
			return (acc);
		}
		free(acc);
	}
	return (NULL);
}

void	
execution(t_nodes *nds, char **env, t_env *tenv)
{
	pid_t	pid;
	char	*cmd;
	char **new_env;

	cmd = NULL;
	new_env = list_to_env(tenv);
	(void)env;
	if (nds->cmd[0])
		built_in(nds,nds->cmd, new_env, &tenv);
	if (nds->cmd[0])
		cmd = acc(nds->cmd[0], tenv);
	if (cmd != NULL)
	{
		signal(SIGINT,SIG_IGN);
		pid = fork();
		if (pid ==0)
		{
			//signal(SIGINT, handler);
			//printf("%s\ncmd : %s\n",nds->cmd[0],cmd);
			signal(SIGINT,&ctrl_c);
			if (nds->cmd[0])
				if (!if_built_in(nds->cmd[0]))
				{
					if(nds->cmd[0][0] == '/' || nds->cmd[0][0] == '.')
						execve(nds->cmd[0],nds->cmd,new_env);
					else
						execve(cmd,nds->cmd,new_env);
				}
			exit(1);
		}
		else
			wait(NULL);
		//printf(UMAG"leak add: %p\n"GREEN,&nds->cmd);
		free(cmd);
	}
/* 	int i = -1;
if(*new_env)
{
	while (new_env[++i])
		free(new_env[i]);
	free(new_env);	
} */
	
}

void	handler(int sig)
{	
	(void)sig;
	exit(0);
	return ;
}

void update_shlvl(t_env *tenv)
{
	while (tenv->next)
	{
		if(strcmp(tenv->key,"SHLVL") == 0)
		{
			tenv->value = ft_itoa(ft_atoi(tenv->value) + 1);
			return ;
		}
		tenv = tenv->next;
	}
	return ;
}


void ctrl_c(int sig)
{
	(void)sig;
	//write(1,"\n",1);
	//rl_done = 1;
	write(1,"\n",1);
	//rl_clear_visible_line();
	rl_replace_line("",0);
	rl_on_new_line();
	rl_redisplay();

}
void ctrl_d(int sig)
{
	//printf("\n\n%d\n\n",sig);
	(void)sig;
	/* printf("bye\n");
	exit(0); */
}
void multi(t_nodes *nds,t_env *tenv,char **env,int size)
{
	int (*fd)[2];
	int i;
	int pid;

	fd = malloc(sizeof(*fd) * size);

	printf("%d\n", size);

	i = -1;
	//*fd = malloc(sizeof(int *) * size);
	while(++i < size)
		pipe(fd[i]);
	while (nds != NULL)
	{
		pid = fork();
		nds ->pid = pid;
		if (pid == 0)
		{
			if(nds->index == 0)
				dup2(fd[0][1],1);
			else if(nds->index == size)
				dup2(fd[nds->index - 1][0],0);
			else
			{
				dup2(fd[nds->index - 1][0],0);
				dup2(fd[nds->index][1],1);
			}
			for (int i = 0; i < size; i++)
			{
				close(fd[i][0]);
				close(fd[i][1]);
			}
			do_infile(nds,tenv,env);
			exit(1);
		}
		
		nds = nds->next;
	}
	i = -1;
	while(++i < size)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	while(wait(0) != -1);
}

void double_proc(t_nodes *nds,t_env *tenv,char **env)
{
	int fd_f[2];
	int pid;
	pipe(fd_f);
	while (nds != NULL)
	{
		pid = fork();
		if(pid == 0)
		{
			if(nds->index == 0)
				dup2(fd_f[1],1);
			else
				dup2(fd_f[0],0);
			close(fd_f[0]);
			close(fd_f[1]);
			do_infile(nds,tenv,env);
			exit(1);
		}
		nds = nds->next;
	}

	close(fd_f[0]);
	close(fd_f[1]);

	while (wait(0) != -1);
}


int main(int ac, char **av, char **env)
{
	int			cpy;
	t_env		*tenv;
	t_nodes		*nds;
	char		*line;
	char		**pipes;
    (void)av;
	(void)ac;
	
	tenv = init_env_tenv(env);
	update_shlvl(tenv);
	printf(GREEN"wellcome to minishell : %s\n","hello");
	signal(SIGINT,&ctrl_c);
	//signal(SIGQUIT,&ctrl_d);
	//signal(SIG)
	rl_catch_signals = 0;
	while(1)
	 {	
		line = readline("😎minishell->");
		if (!line)
		{
			printf("exit\n");
			exit(1);
		}
		if (line[0])
			add_history(line);
		else
		{
			printf(UMAG"leak add: %p\n"GREEN,&tenv);
			continue ;
		}
		cpy = dup(0);
		pipes = ft_split(line, '|');
		nds = init_nodes(pipes);			

		//print_nodes(nds);
		if(mat_len(pipes) == 2)
			double_proc(nds,tenv,env);
		else if(mat_len(pipes) > 2)
			multi(nds,tenv,env,mat_len(pipes) - 1);
		else
			while(nds!= NULL)
		{
			int i = -1;
			do_hrd(nds);
			do_infile(nds,tenv,env);
			if(*nds->append)
				while(nds->append[++i])
					append_redirect(nds->append[i]);
				//do_outfile(nds,tenv,env);
			nds = nds->next;
			dup2(cpy,0);
			close(cpy);
		}
	 }
    return (0);
}
