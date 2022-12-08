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
		pid = fork();
		if (pid ==0)
		{
			//signal(SIGINT, handler);
			printf("%s\ncmd : %s\n",nds->cmd[0],cmd);
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
		printf(UMAG"leak add: %p\n"GREEN,&nds->cmd);
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

void do_doub(t_nodes *nds,t_env *tenv,int *input,int *output,char **env)
{
	int proc;

	proc = fork();
	if (proc == 0)
	{
		if (input != NULL)
		{
			close(input[1]);
			dup2(input[0],STDIN_FILENO);
		}
		if (output != NULL)
		{
			close(output[0]);
			dup2(output[1],1);
		}
		do_infile(nds,tenv,env);
		
	}
	
}

void double_proc(t_nodes *nds,t_env *tenv,char **env)
{
	int fd_f[2];
	int fd_s[2];

	pipe(fd_f);
	pipe(fd_s);
	do_doub(nds,tenv,NULL,fd_f,env);
	while (nds != NULL)
	{
		if(nds->index % 2 == 0)
			do_doub(nds,tenv,fd_f,fd_s,env);
		else
			do_doub(nds,tenv,fd_s,fd_f,env);	
		nds = nds->next;
	}
	
}
void ctrl_c(int sig)
{
	(void)sig;
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
	//signal(SIGINT,&ctrl_c);
	//signal(SIGQUIT,&ctrl_d);
	//signal(SIG)
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
		/* if(mat_len(pipes) == 1)
			single_proc(nds,tenv,env);
		else
			multi_proc(nds,tenv,env); */
			//dup2(cpy,0);
		/* char **test = list_to_env(tenv);
		if(test[0])
			printf("hello\n");
		int i = -1;
		while (test[++i])
			printf(UMAG" test 1 :%s\n",test[i]); */
		
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
