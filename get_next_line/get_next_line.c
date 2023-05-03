#include "get_next_line.h"

int ft_strlen(char *str)
{
    int i;
    
    if (str == NULL)
        return 0;
    i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}


char *ft_strjoin(char *str1, char *str2)
{
    int i;
    int j;

    int size_str1;
    int size_str2;
    int size_result;
    char *result;
    
    if (str1 == NULL && str2 == NULL) {
        return (NULL);
    }

    size_str1 = ft_strlen(str1);
    size_str2 = ft_strlen(str2);
    size_result = size_str1 + size_str2 + 1;

    result = malloc(sizeof(char) * size_result);
    if (result == NULL)
        return (NULL);
    
    i = 0;
    while (i < size_str1)
    {
        result[i] = str1[i];
        i++;
    }
    
    j = 0;
    while (j < size_str2) {
        result[i] = str2[j];
        i++;
        j++;
    }
    
    result[i] = '\0';
    return result;
}

char *ft_strdup(char *str)
{
    int size_str;
    char *result;
    int i;

    if (str == NULL)
        return NULL;

    size_str = ft_strlen(str);

    result = malloc(sizeof(char) * (size_str + 1));
    if (result == NULL)
        return NULL;

    i = 0;
    while(i < size_str)
    {
        result[i] = str[i];
        i++;
    }
    result[i] = '\0';
    return result;
}


char *extract_line(char *str, int n)
{
    
    char    *result;
    int     i;

    if (str == NULL)
        return NULL;
    /*
    if (ft_strlen(str) <= n)
        return ft_strdup(str);
    */
    result = malloc(sizeof(char) * (n + 2));
    if (result == NULL)
        return NULL;

    i = 0;
    while(i < n)
    {
        result[i] = str[i];
        i++;
    }
    result[n] = '\n';
    result[n+1] = '\0';

    return result;
}

int bn_in_str(char *str)
{
    int i;

    if (str == NULL)
    {
        return (-1);
    }

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\n')
        {
            return (i);
        }
        i++;
    }
    return -1;
}


char *trim_stash(char *stash)
{
    int i;
    char *tmp;
    int size_stash;
    int new_size_stash;

    i = bn_in_str(stash);
    size_stash = ft_strlen(stash);

    new_size_stash = size_stash - i;
    
    tmp = ft_strdup(stash+i+1);
    free(stash);
    stash = NULL;
    stash = ft_strdup(tmp);
    free(tmp);
    tmp = NULL;
    return stash;
} 

char *get_next_line(int fd)
{
    char buf[BUFFER_SIZE + 1];
    static char* stash;
    int caract_read;
    char *tmp;
    char *line;

    tmp = NULL;
    line = NULL;
    //buf = malloc((BUFFER_SIZE+1)*sizeof(char));

    if (fd < 0 || BUFFER_SIZE <= 0)
    {
        return NULL;
    }


    caract_read = read(fd, buf, BUFFER_SIZE);
    if (caract_read == -1)
    {
        if (stash != NULL)
        {
            free(stash);
            stash = NULL;
        }
        //printf("inutile d aller plus loin\n");
        return(NULL);
    }

    buf[caract_read] = '\0';

    
    while (caract_read > 0)
    {
        tmp = ft_strjoin(stash, buf);
        if (stash != NULL)
        {
            free(stash);
            stash = NULL;
        }

        stash = ft_strdup(tmp);
        free(tmp);
        tmp = NULL;

        if (bn_in_str(stash) != -1)
        {
            line = extract_line(stash, bn_in_str(stash));
            stash = trim_stash(stash);
            return line;
        }
        
        caract_read = read(fd, buf, BUFFER_SIZE);
        if (caract_read == -1)
        {
            if (stash != NULL)
            {
                free(stash);
                stash = NULL;
            }
            //printf("inutile d aller plus loin\n");
            return(NULL);
        }
        buf[caract_read] = '\0';
    }
    
    if (bn_in_str(stash) != -1 && ft_strlen(stash) > 0)
    {
        line = extract_line(stash, bn_in_str(stash));
        stash = trim_stash(stash); 
        return line;
    }

    if (bn_in_str(stash) == -1 && ft_strlen(stash) > 0)
    {
        line = ft_strdup(stash);
        free(stash);
        stash = NULL;
        return (line);
    }

    if (stash != NULL && ft_strlen(stash) == 0)
    {
        free(stash);
        stash = NULL;
    }

    return NULL;        
}


/*
int main ()
{
    char *line;
    int fd;
    int i;
    
    printf("Test basique :\n");
    fd = open("test", O_RDONLY);
    i = 0;
    while (line)
    {
        line = get_next_line(42);
        printf("line %d = [%s]\n",i, line);
        free(line);
        i++;
    }
    
    return 0;
}*/
