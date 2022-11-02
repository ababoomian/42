# include "./minishell.h"

void g_to_home(t_table *tab,char **rl)
{
	int i;

	tab->home = "";
	i  = -1;
	while (tab->env[++i])
		if(!strncmp(tab->env[i],"HOME",4))
		{
			tab->env[i] += 5;
			tab->home =ft_strjoin(tab->home,tab->env[i]);
		}
	if(!rl[1])
		chdir(tab->home);
	else if(ft_strlen(rl[1]) > 2)
	{
		rl[1] += 2;
		chdir(tab->home);
		chdir(rl[1]);
	}
	else
		chdir(tab->home);
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

void cd(t_table *tab,char **read_line)
{
	int i;
	char c[1024];
	//char *str;
	getcwd(c,1024);
	i = -1;
	while (tab->env[++i])
		if(!strncmp(tab->env[i],"OLDPWD=",7))
		{
			tab->pwd  =c;
			tab->env[i] = ft_strjoin("OLDPWD=",c);
		}
	i = -1;
	if(read_line[1])
		while(*read_line[1] && *read_line[1] == 32)
			read_line++;
	if(!read_line[1] || *read_line[1] == '~' || *read_line[1] == '-')
	{
		g_to_home(tab,read_line);
		return;
	}
	
	else if(chdir(read_line[1]) == 0)
	{
		while (tab->env[++i])
			if(!strncmp(tab->env[i],"PWD=",4))
			{				
				getcwd(c,1024);
				tab->env[i] = ft_strjoin("PWD=",c);
			}
	}
	else
		printf(CYELLOW"no shuch a file or directory\n"GREEN); 
	//free(c);
}