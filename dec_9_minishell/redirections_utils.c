# include "./minishell.h"

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
				
				heredoc_redirect(nds->heardock[i]);
			}
			else
				simple_hrd(nds->heardock[i]);
		}
	}
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