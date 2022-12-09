# include "./minishell.h"

int heredoc_count(char *str)
{
	int i;
	int res;

	i = -1;
	res = 0;
	while (str[++i])
	{
		if(str[i] == '<')
		{
			i++;
			if (str[i] && str[i] == '<')
				res++;
		}
	}
	return(res);
}


char **hd_init(char *str)
{
	int i;
	int j;
	int start;
	int end;
	char **res;

	end = 0;
	res = malloc(sizeof(char *) * heredoc_count(str));
	j = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '<')
		{
			i++;
			if(str[i] && str[i] == '<')
			{
				i++;
				start = i;
				/* while(str[i] && (str[i] == ' ' || str[i] == '<' || str[i] == '>'))
				{
					end++;
					i++;
				} */
				while(str[i] && (str[i] != ' ' || str[i] != '<' || str[i] != '>'))
				{
					//printf("hello\n");
					end++;
					i++;
				}
				res[j] = ft_substr(str,start,end + 1);
				printf("%s\n",res[j]);
				j++;
				end = 0;
				
			}
		}
		
	}
	return(res);
}