#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
# include "./minishell.h"
# define METATEGS ""
void print_nodes(t_nodes *head) {

    t_nodes *current = head;
	int i;
   	while ( current != NULL ) 
	{
		i = -1;
		while(current->heardock[++i])
	    	printf(CYELLOW"heredoc: %d : %s\n"GREEN,i,current->heardock[i]);
		//i = -1;
		//while(current->cmd[++i])
			//printf(CYELLOW"cmd : %s\n"GREEN,current->cmd[i]);
        current = current->next;
    }
}


/* static int	is_number(char c)
{
	if(c >= '0' && c <= '9')
		return (1);
	return (0);
} */

/* static int	is_printable(char c)
{
	if (c <= 32 && c  > 126)
		return (0);
	return (1);
} */
int		hd_count(char *str)
{
	int	i;
	int j;
	i = 0;
	j = 0;
	if(!str)
		return 0;
	while(str[i])
	{
		if((str[i] == '<' && str[i + 1] == '<') && str[i + 1] != '\0')
		{
				i += 2;
				j += 2;
				while(str[i] != ' ' && str[i])
				{
					i++;
					j++;
				}
		}
		j++;
		i++;
	}
	return j;
}
char	**heardock_init(char *str)
{
	int	i;
	int j;
	char *res;
	res = malloc(sizeof(char) * hd_count(str) + 1);
	i = 0;
	j = 0;
	if(!str)
		return NULL;
	
	while(str[i])
	{
		if((str[i] == '<' && str[i + 1] == '<') && str[i + 1] != '\0')
		{
				res[j++] = str[i];
				res[j++] = str[i + 1];
				i += 2;
				while(str[i] && str[i] == 32 )
					i++;
				while(str[i] != ' ' && str[i])
				{
					res[j] = str[i];
					i++;
					j++;
				}
		}
		res[j] = ' ';
		j++;
		i++;
	}
	res[j] = '\0';
	printf("%s\n", res);
	//while(1);
	return ft_split(res, ' ');
}

int		append_cnt(char *str)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = 0;
	if(!str)
		return 0; //empty case check:
	while(str[i])
	{
		if(str[i] == '>' && str[i + 1] == '>')
		{
			cnt++;
			while(str[i] && str[i] != ' ')
				i++;
		}
		i++;
	}
	return cnt;
}
int		infile_cnt(char *str)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = 0;
	if(!str)
		return 0; //empty case check:
	while(str[i])
	{
		if(str[i] == '<' && str[i + 1] != '<' && str[i + 1])
			cnt++;
		else if(str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			return (0); // exit(0)
		i++;
	}
	return cnt;
}

int		outfile_cnt(char *str)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = 0;
	if(!str)
		return 0; //empty case check:
	while(str[i])
	{
		if(str[i] == '>' && str[i + 1] != '>')
			cnt++;
		i++;
	}
	return cnt;
}

/* char *parsed_str_lst(char *str)
{
	int	i;
	char	*res;
	int	trim_size;
	int	j;

	j = 0;
	trim_size = ft_strlen(str) - ( heardock_cnt(str) - infile_cnt(str) - outfile_cnt(str) - append_cnt(str));
	res = (char*)malloc(sizeof(char) * trim_size + 1);
	i = 0;
	while(str[i])
	{
		res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return res;

} */

 t_nodes	*new_nodes(int i,char **mx)
{
	t_nodes *inited;
	inited = NULL;
	inited = (t_nodes*)malloc(sizeof(t_nodes));
	if(inited == NULL)
		return (NULL);
		inited->heardock = heardock_init(mx[i]);
		inited->next = NULL;
	return(inited);
}

t_nodes *init_nodes(char **mx)
{
	int	i;
	int	len;
	t_nodes *inited;
	t_nodes *tmp;
	inited = NULL;
	//inited = (t_nodes*)malloc(sizeof(t_nodes));
	len = mat_len(mx);
	i = 0;
	inited = new_nodes(i,mx);
	tmp = inited;
	while(++i < len)
	{
		tmp = new_nodes(i,mx);
		tmp = inited->next;
	}
	//inited->next = NULL;
	return inited;
}


/*
func(mx)
{
	int i = 0;
	while(strlen)
		if(APPEND || OUTFILE || INFILE || HRD)
			i++;
		res = malloc ((sizeof(char) * i )+ 1);
		i = 0;
		while(mx)
			if(mx[i] == APP)
				APP +=1;


}



*/