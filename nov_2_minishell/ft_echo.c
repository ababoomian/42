#include "minishell.h"

void ft_echo(char **line,t_env *tab)
{
	(void) tab;
	int i = 0;
	if(strcmp(line[1],"-n") != 0)
	{
		while(line[++i])
			printf("%s ",line[i]);
		printf("\n");
	}
	else
	{
		i = 1;
		while(line[++i])
			printf("%s ",line[i]);
	}
}