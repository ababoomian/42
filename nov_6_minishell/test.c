#include "./minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **push_mat(char **str,char *to_be_push)
{
	char **res;
	int i;

	i = -1;
	res = malloc(sizeof(char *) * mat_len(str) + 1);
	if(!res)
		return(NUll);
	while(++i < mat_len(str))
		res[i] == str[i];
	res[i] = to_be_push;
	i++;
	res[i] = 0;
	return(res);
}


char *gnl(int fd)
{
    int 	i = 0;
    int 	rd = 0;
    char	character;
    char 	*buffer = malloc(10000);

    while ((rd = read(fd, &character, 1)) > 0)
    {
        buffer[i++] = character;
        if (character == '\n')
            break;
    }
    if ((!buffer[i - 1] && !rd) || rd == -1)
    {
        free(buffer);
        return (NULL);
    }
    buffer[i] =  '\0';
	close(fd);
    return(buffer);
}


int main(int ac,char **av,char **env)
{
	
}