#include "../includes/minishell.h"

void    *ft_malloc(size_t nmemb, size_t size, t_exec *exec)
{
    void    *ptr;
    static t_exec *global_exec = NULL;

    if (exec != NULL)
    {
        global_exec = exec;
        return (NULL);
    }
    else
    {
        ptr = malloc(nmemb * size);
        if (!ptr)
        {
            perror("malloc");
            free_exec(global_exec);
            exit(12);
        }
        return (ptr);
    }
}
