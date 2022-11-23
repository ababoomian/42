/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 04:05:26 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/11/23 12:32:33 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
# include "./minishell.h"

int	shlvl = 1;
int	sigint = 0;

void	ft_getenv(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

void	built_in(t_nodes *nds, char **read_lide, char **env, t_env **tenv)
{
	(void)nds;
	(void)env;
	if (!strcmp(read_lide[0], "pwd"))
	{
		char	c[1024];
		getcwd(c, 1024);
		printf("%s\n", c);
	}
	else if (strcmp(read_lide[0], "cd") == 0 )
		cd(tenv, read_lide);
	else if (strcmp(read_lide[0], "env") == 0)
		print_list_tenv(*tenv);
	else if (!strcmp(read_lide[0], "exit"))
		ft_exit(read_lide);
	else if (strcmp(read_lide[0], "echo") == 0)
		ft_echo(read_lide, *tenv);
	else if (strcmp(read_lide[0], "export") == 0)
		ft_main_export(tenv, read_lide);
	else if (strcmp(read_lide[0], "unset") == 0)
		 multi_unset(tenv, read_lide);
}

int	if_built_in(char *str)
{
	if (!strcmp(str, "pwd") || !strcmp(str, "cd") || !strcmp(str, "echo")
		|| !strcmp(str,"export") || !strcmp(str,"unset") || !strcmp(str, "env") 
		|| !strcmp(str, "exit") || !strcmp(str, APPEND) || !strcmp(str, INFILE)
		|| !strcmp(str, OUTFILE) || strncmp(str, "<<", 1) == 0)
		return (1);
	else
		return (0);
}

t_table	*create_table(char **env)
{
	t_table		*tab;
	int			i;

	i = 0;
	tab = malloc(sizeof(t_table));
	tab->env = env;
	while (env[i])
	{
		if (strncmp("PATH=", env[i], 5) == 0)
		{
			env[i] += 5;
			tab->path = ft_split(env[i], ':');
		}
		if (strncmp("PWD=", env[i], 4) == 0)
			tab->pwd = env[i];
		i++;
	}
	i = -1;
	return (tab);
}

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
	return (NULL);
}

void simple_hrd(char *str)
{
	char	*s;
	int		fd;
	int		i;
	char	*file;

	file = ft_strjoin(".", str);
	i = 0;
	str += 2;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '-')
		{
			printf("%s\n", "syntax error near unexpected token `<'");
			return ;
		}
		i++;
	}
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	printf("heredoc-redirect: %s : %d\n", str, fd);
	while (1)
	{
		s = readline(CYELLOW"heredoc: "GREEN);
		if (strcmp(str, s) == 0)
			break ;
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
		free(s);
		s = NULL;
	}
	close(fd);
	unlink(file);
	free(file);
	
}

void	do_hrd(t_nodes *nds)
{
	int	i;
	int len;

	len = mat_len(nds->heardock);
	i = -1;
	if (*nds->heardock)
	{		
		while (nds->heardock[++i])
		{
			if(i == len - 1)
			{
				printf("main hrddd\n");	
				heredoc_redirect(nds->heardock[i]);
			}
			else
				simple_hrd(nds->heardock[i]);
		}
	}
}

void	do_outfile(t_nodes *nds, t_env *tenv, char **env)
{
	int		fd_tmp;
	int		i;

	i = -1;
	if (*nds->infile)
	{	
		i = -1;
		fd_tmp = dup(1);
		while (nds->infile[++i])
		{
			outfile_redirect(nds->infile[i]); 
			if (nds)
				execution(nds, env, tenv);
		}
		dup2(fd_tmp, STDOUT_FILENO);
	}
	else
		execution(nds, env, tenv);
}

void	do_infile(t_nodes *nds,t_env *tenv, char **env)
{
	int		fd_tmp;
	int		i;

	i = -1;
	if (*nds->infile)
	{	
		i = -1;
		fd_tmp = dup(1);
		while (nds->infile[++i])
		{
			 infile_redirect(nds->infile[i], fd_tmp);
			if (nds)
				execution(nds, env, tenv);
		}
		dup2(fd_tmp, 1);
	}
	else
		execution(nds, env, tenv);
}

void	execution(t_nodes *nds, char **env, t_env *tenv)
{
	pid_t	pid;
	char	*cmd;

	cmd = NULL;
	(void)tenv;
	if (nds->cmd[0])
		built_in(nds,nds->cmd, env, &tenv);
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
						execve(nds->cmd[0],nds->cmd,env);
					else
						execve(cmd,nds->cmd,env);
				}
			exit(1);
		}
		else
			wait(NULL);
	}
}

void	handler(int sig)
{	
	(void)sig;
	sigint  = 1;
	return ;
}

int main(int ac, char **av, char **env)
{
	int			cpy;
	t_env		*tenv;
	t_nodes		*nds;
	char		*line;
	char		**pipes;
	shlvl++;
    (void)av;
	(void)ac;

	tenv = init_env_tenv(env);		
	printf(GREEN"wellcome to minishell : %d\n",shlvl);
	while(1)
	 {	
		line = readline("😎minishell->");
		if (!line)
			exit(1);
		if (line[0])
			add_history(line);
		else
			continue ;
		cpy = dup(0);
		pipes = ft_split(line, '|');
		nds = init_nodes(pipes);
		print_nodes(nds);
		/* if(mat_len(pipes) == 1)
			single_proc(nds,tenv,env);
		else
			multi_proc(nds,tenv,env); */
			//dup2(cpy,0);
		/* while(nds!= NULL)
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
			//close(cpy);
		} */
	 }
    return (0);
}
