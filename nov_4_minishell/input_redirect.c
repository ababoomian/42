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
	rd = 0;
	while((rd = read(fd, &ch, 1)) > 0)
		s[i++] = ch;
	if((!s[i - 1] && !rd) || rd == -1)
	{
		free(s);
		return (NULL);
	}
	s[i] = '\0';
	return (s);
}

void	infile_redirect(char *str, char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_CREAT, 0644);
	if(fd > 0)
	{
		write(fd, str, ft_strlen(str));
		close(fd);
	}
	return ;
}

void	outfile_redirect(char *str)
{
	int	fd;
	char	*s;
	s = NULL;

	fd = open(str, O_RDONLY);
	if(fd == -1)
		return ;
	if(s)
		dup2(0, fd);
	s = gnl(fd);
	close(fd);
	free(s);
}

void	append_redirect(char *str, char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	if(fd > 0)
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		close(fd);
	}
	return ;
}

void	heredoc_redirect(char *str)
{
	char *s;
	int fd;
	int	i;

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
	fd = open(".heredoc", O_RDWR | O_CREAT, 0644);
	printf("heredoc-redirect: %s\n", str);
	while(1)
	{
		s = readline(CYELLOW"heredoc: "GREEN);
		if(!strcmp(str, s))
		{
			write(fd, str, ft_strlen(str));
			break;
		}
		free(s);
		s = NULL;
	}
	dup2(0, fd);
	unlink(".heredoc");
	close(fd);
}