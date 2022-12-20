#include "./minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int ac,char **av,char **env)
{
	(void)ac;
	execve("/bin/ls", ++av, env);	
}