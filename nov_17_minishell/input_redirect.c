#include "./minishell.h"

int	gnl_cnt(int fd)
{
	int	rd;
	char	ch;
	int	len;

	rd = 0;
	len = 0;
	while((rd = read(fd, &ch, 1)) > 0)
		len++;
	return len;
}

char	*gnl(int fd)
{
	int	rd;
	int	i;
	char	*s;
	char	ch;
	int	len;

	rd = 0;
	i = 0;
	len = 0;
	s = malloc(gnl_cnt(fd) + 1);
	//s = malloc(10000);
	while((rd = read(fd, &ch, 1)) > 0)
		s[i++] = ch;
	if((!s[i - 1] && !rd) || rd == -1)
	{
		free(s);
		return (NULL);
	}
	s[i] = '\0';
	printf("result of gnl %s\n", s);
	return (s);
}

 void	infile_redirect(char *file,int fd_s)
{
	 (void) fd_s;
	int fd = open(++file,O_WRONLY | O_CREAT | O_TRUNC , 0644);
	dup2(fd,1);
	close(fd);	
}

void	outfile_redirect(char *str)
{
	int	fd;
	char	*s;
	s = NULL;

	fd = open(++str, O_RDONLY);
	if(fd == -1)
		return ;
	//if(s)
		dup2(1, fd);
	s = gnl(fd);
	write(1,s,ft_strlen(s));
	close(fd);
	free(s);
}

void	append_redirect(char *file)
{
	int fd;

	fd = open(++file, O_RDWR | O_APPEND, 0644);
	if(fd > 0)
	{
		dup2(fd,1);
		write(fd, "\n", 1);
		close(fd);
	}
	else
	{
		write(2,"no such a file or directory\n",29);
		return ;
	}
	return ;
}

void	heredoc_redirect(char *str)
{
	//int cpy = dup(0);
	char *s;
	int fd;
	int	i;
	char *file;

	file = ft_strjoin(".",str);
	i = 0;
	str+=2;
	while(str[i])
	{
		if(str[i] == '<' || str[i] == '>' || str[i] == '-')
		{
			printf("%s\n", "syntax error near unexpected token `<'");
			return ;
		}
		i++;
	}
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	printf("heredoc-redirect: %s : %d\n", str,fd);

	while(1)
	{
		s = readline(CYELLOW"heredoc: "GREEN);
		if(strcmp(str, s) == 0)
			break;
		write(fd, s, ft_strlen(s));
		write(fd,"\n",1);
		free(s);
		s = NULL;
	}

	close(fd);
	fd = open(file,O_RDONLY );
	dup2(fd, 0);
	//close(0);
	close(fd);
	unlink(file);
	free(file);
}