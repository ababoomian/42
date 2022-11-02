# include "minishell.h"

char *epur_str(char *str)
{
	int i;
	int flg;
	int j = 0;
	char *res;
	res = malloc(sizeof(char) * 200 + 1);

	if (str && *str)
	{
		i = 0;
		while (str[i] == ' ' || str[i] == '\t'  /* || str[i] == '\'' || str[i] == '\"' */)
			i += 1;
		while (str[i])
		{
			if (str[i] == ' ' || str[i] == '\t'  )
				flg = 1;
			if (!(str[i] == ' ' || str[i] == '\t'/*  || str[i] == '\'' || str[i] == '\"' */))
			{

				if (flg)
				{
					res[j] = 32;
					j++;
				}
				flg = 0;
				res[j] = str[i];
				j++;
			}
			i += 1;
		}
		res[j] = '/';
	}
	return (res);
} 