#include "../../includes/minishell.h"

static t_env *get_var(t_exec *exec, char *name)
{
    t_env *var;
    t_env *res;
    
    var = exec->env;
    while(var)
    {
        if (!ft_strncmp(var->name, name, ft_strlen(name) + ft_strlen(var->name)))
            return (var);
        if (var->next != NULL)
            var = var->next;
        else
            break;
    }
    res = malloc(sizeof(t_env));
    res->name = NULL;
    res->value = NULL;
    res->next = NULL;
    res->exported = 1;
    var->next = res;
    return (res);
}

static int	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void ft_export(t_exec *exec)
{
    char    **args;
    char    *name;
    char    *value;
    t_env   *var;

    args = create_args(exec);
    if (args[1] == NULL)
        ft_env(exec);
    else
    {
        name = get_var_name(args[1]);
        if (valid_identifier(name) == 0)
        {
            printf("export: \'%s\': not a valid identifier\n", args[1]);
            return ;
        }
        value = get_var_value(args[1]);
        var = get_var(exec, name);
        var->name = ft_strdup(name);
        var->value = ft_strdup(value);
        free(name);
        free(value);
        free_tab(args);
    }
}
