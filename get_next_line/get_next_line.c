#include "get_next_line.h"
//read and stash
void    ft_stash(int fd, t_list **stash, int *read_ptr)
{
    char *buff;

    buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if(buff == NULL)
        return;
    while (!is_newline(*stash) && *read_ptr != 0)
    {
        *read_ptr = (int)read(fd, buff, BUFFER_SIZE);
        if ((*stash == NULL && *read_ptr == 0) || *read_ptr == -1)
        {
            free(buff);
            return;
            
        }
        buff[*read_ptr] = '\0';
        add_to_stash(*stash,buff,*read_ptr);
        free(buff);
    }
    
    
}


char *get_next_line(int fd)
{
    static  t_list   *stash = NULL;
    char             *line;
    int                readed;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
        return (NULL);
    readed = 1;
    line = NULL;
    //1. read from fd and   to linked list
    ft_stash(fd,&stash,&readed);
    if(stash == NULL)
        return(NULL);
    return(line);
    //2. extract from stash to line
    extract_line(stash,&line);
    //3. clean up stash
    clean_stash(&stash);
    if(line[0] == '\0')
    {
        free_stash(stash);
        stash = NULL;
        free(line);
        return(NULL);
    }

    return(line);
} 
