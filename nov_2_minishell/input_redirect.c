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

	fd = open(file, O_RDWR | O_CREAT, 0777);
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
	//read(0,s,ft_strlen(s));
	close(fd);
	free(s);
}
/* static char	*gnl_nl(int fd)
{
	int	rd;
	int	i;
	char	*s;
	char	ch;
	int	len;

	rd = 0;
	i = 0;
	len = 0;
	s = malloc(10000);
	rd = 0;
	while((rd = read(fd, &ch, 1)) > 0)
	{
		s[i++] = ch;
		if(ch == '\n')
			break ;
	}
	if((!s[i - 1] && !rd) || rd == -1)
	{
		free(s);
		return (NULL);
	}
	s[i] = '\0';
	return (s);
} */
void	append_redirect(char *str, char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0777);
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
	int fd = open(".heredoc", O_RDWR | O_CREAT, 0777);
	while(1)
	{
		s = readline(CYELLOW"hrd>"GREEN);
		if(!strcmp(str, s))
		{
			write(fd, str, ft_strlen(str));
			break;
		}
		free(s);
		s = NULL;
	}
	dup2(0, fd);
	close(fd);
}