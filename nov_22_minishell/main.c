/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 04:05:26 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/12/03 23:36:05 by arbaboom         ###   ########.fr       */
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

	i = -1;
	path = find_path(tenv);
	if (access(cmd, 0) == 0)
			return (cmd);
	if (path == NULL)
		return (NULL);
	else if (cmd[0] == '/')
		return (cmd);
	while (path[++i])
	{
		acc = ft_strjoin(path[i], ft_strjoin("/", cmd));
		if (access(acc, 0) == 0)
			return (acc);
		free(acc);
	}
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
	
	return (NULL);
}

void	execution(t_nodes *nds, char **env, t_env *tenv)
{
	pid_t	pid;
	char	*cmd;
	char **new_env;

	cmd = NULL;
	new_env = list_to_env(tenv);
	(void)tenv;
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
			signal(SIGINT, handler);
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
	while(1)
	 {	
		line = readline("😎minishell->");
		if (!line)
			exit(1);
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
