#include "../../includes/minishell.h"

void ft_pwd(void)
{
    char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
		printf("%s\n", cwd);
    else
        perror("pwd");
}
