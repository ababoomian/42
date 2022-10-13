#include "get_next_line.h"
int is_newline(t_list *stash)
{
    int i;
    t_list  *current;

    if (stash == NULL)
        return (0);
    current = ft_lstlast(stash);
    i =0;
    while (current -> content[i])
    {
        if (current -> content[i] == '\n')
            return (1);
        i++;
    }
    return (0);
    
}

t_list *ft_lstlast(t_list *stash)
{
    t_list *current;

    current = stash;
    while (current && current ->next)
        current = current -> next;
    return (current);
}

void add_to_stash(t_list *stash, char *buff, int readed)
{
    int i;
    t_list *last;
    t_list *new_node;

    new_node = malloc(sizeof(t_list));
    if(new_node == NULL)
        return;
    new_node -> next = NULL;
    new_node -> content = malloc(sizeof(char) * (readed + 1));
    if(new_node -> content == NULL)
        return;
    i = 0;
    while (buff[i] && i < readed)
    {
        new_node -> content[i] = buff[i];
        i++;
    }
    new_node -> content[i] = '\0';
    if(stash == NULL)
    {
        *stash = *new_node;
        return;
    }
      last = ft_lstlast(stash);
      last -> next = new_node;
}


void extract_line(t_list *stash, char **line)
{
    int i;
    int j;

    if (stash == NULL)
        return;
    generate_line(line, stash);
    if(*line == NULL)
        return;
        j = 0;
        while(stash)
        {   
            i = 0;
            while(stash -> content[i])
            {
                if(stash -> content[i] == '\n')
                {
                    (*line)[j] = stash -> content[i];
                    break;
                }
                j++;
                (*line)[j++] = stash -> content[i++];
            }
        } 
        stash = stash -> next; 
    
    (*line)[j] = '\0';  
}

void generate_line(char **line,t_list *stash)
{
    int i;
    int len;

    len = 0;
    while(stash)
    {
        i = 0;
        while(stash -> content[i])
        {   
            if(stash -> content[i] == '\n')
            {
                len++;
                break;
            }
            len++;
            i++;
        }
        stash = stash -> next;
    }
    *line = malloc(sizeof(char) * (len +1));
}

void clean_stash(t_list **stash)
{
    t_list *last ;
    t_list *clean_node;
    int i;
    int j;

    clean_node = malloc(sizeof(t_list));
    if(stash == NULL || clean_node == NULL)
        return;
    clean_node -> next = NULL;
    last = ft_lstlast(*stash);
    i = 0;
    while(last ->content[i] && last -> content[i] != '\n')
        i++;
    if(last -> content && last ->content[i] == '\n')
        i++;
    clean_node -> content = malloc(sizeof(char) * (ft_strlen(last -> content) - i) + 1);
    if(clean_node -> content == NULL)
        return;
    j = 0;
    while(last -> content[i])
        clean_node -> content[j++] = last -> content[i++];
    clean_node -> content[j] = '\0';
    free_stash(*stash);
    *stash = clean_node;

}

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    while(str[i] != 0)
        i++;
    return (i);
}

void free_stash(t_list  *stash)
{
    t_list *current;
    t_list *next;

    current = stash;

    while(current)
    {
        free(current -> content);
        next = current -> next;
        free(current);
        current = next;
    }
}