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
            exit(1);
        }
        return (ptr);
    }
}

void exit_malloc_failure(t_exec *exec)
{
    static t_exec *global_exec;

    if (exec != NULL)
        global_exec = exec;
    else
    {
        ft_putstr_fd("minishell: Memory error. Please check available memory !\n", 2);
        free_exec(exec);
        exit(1);
    }
}
