#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFFER_SIZE 8


int search_EOL(char *str)
{
    int i;
    
    i = 0;
    return 0;
    
    
    
}

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
        
    result = malloc(sizeof(char) * size_result);
    if (result == NULL) {
        return (NULL);
    }
    
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


char *ft_strndup(char *str, int n)
{
    int     size_str;
    char    *result;
    int     i;

    if (str == NULL)
        return NULL;

    if (ft_strlen(str) <= n)
    {
        return ft_strdup(str);
    }

    result = malloc(sizeof(char) * (n + 1));
    if (result == NULL)
        return NULL;

    i = 0;
    while(i < n)
    {
        result[i] = str[i];
        i++;
    }
    result[n] = '\0';
    //printf("strndup = %s\n", result);
    return result;
}



int bn_in_str(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\n')
        {
            return (i);
        }
        i++;
    }
    return 0;
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

    
    tmp = ft_strndup(stash+i+1, new_size_stash-1);

    
    //printf("r = %s\n", tmp);


    return tmp;

} 

char *get_next_line(fd)
{
    char buf[BUFFER_SIZE + 1];
    static char* stash;
    size_t caract_read;
    char *tmp;
    char *line;

    stash = NULL;
    caract_read = 1;
    tmp = NULL;
    line = NULL;

    //caract_read = read(fd, buf, BUFFER_SIZE);
    //buf[BUFFER_SIZE] = '\0';
    
    while (caract_read > 0)
    {

        caract_read = read(fd, buf, BUFFER_SIZE);
        buf[BUFFER_SIZE] = '\0';
        
        if (caract_read == BUFFER_SIZE) 
        {
            tmp = ft_strjoin(stash, buf);
            if (stash != NULL)
            {
                stash = NULL;
                free(stash);
            }

            stash = ft_strdup(tmp);
            tmp = NULL;
            free(tmp);

            if (bn_in_str(stash) > 0)
            {
                line = ft_strndup(stash, bn_in_str(stash));
                tmp = trim_stash(stash);
                stash = NULL;
                free(stash);
                
                stash = ft_strdup(tmp);
                tmp = NULL;
                free(tmp);   
                return line;
            }
            
        }
    }
    /*
    else if (caract_read < BUFFER_SIZE && caract_read > 0)
    {
        // on a atteint la fin du fichier 
        printf("EOF\n");

    }
    else
    {
        printf("aucun caractere lu\n");

    }
    */
    
    
    
    return NULL;
    
    
}



int main ()
{
    char *line;
    int fd;
    int i;

    fd = open("test", O_RDONLY);

    i = 0;
    while (i < 5)
    {
        line = get_next_line(fd);
        printf("line = [%s]\n", line);
        i++;
    }



    //trim_stash("123456\n789");
    
    //printf("test dup = %s\n", ft_strdup("ca joue grave"));
    //ft_strndup("tk",4);
    
    //printf("bn   = %d\n", bn_in_str("0123\nkjkjkjkj"));
    
    return 0;
}
