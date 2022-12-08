# include "./minishell.h"

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

void	ft_getenv(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
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