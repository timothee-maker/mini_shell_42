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

static void	sort_tab(char **tab, int len)
{
	int	i;
	int	j;
	int	diff;
    char *temp;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			diff = ft_strncmp(tab[i], tab[j], INT_MAX);
			if (diff > 0)
			{
				temp = tab[i];
	            tab[i] = tab[j];
	            tab[j] = temp;
				continue ;
			}
			j++;
		}
	i++;
	}
}

static int no_args(t_exec *exec)
{
    char **tab;
    int i;

    i = 0;
    tab = str_env(exec);
    sort_tab(tab, len_tab(tab));
    while(tab[i])
    {
        printf("export %s\n", tab[i]);
        i++;
    }
    return (0);
}

int ft_export(t_exec *exec, t_cmd *cmd)
{
    char    *name;
    char    *value;
    t_env   *var;

    if (cmd->args[1] == NULL)
    {
        return(no_args(exec));
    }
    else
    {
        name = get_var_name(cmd->args[1]);
        value = get_var_value(cmd->args[1]);
        if (name == NULL || value == NULL)
        {
            if (name)
                free(name);
            if (value)
                free(value);
            return (0);
        }
        if (valid_identifier(name) == 0)
        {
            printf("export: \'%s\': not a valid identifier\n", cmd->args[1]);
            return (2);
        }
        var = get_var(exec, name);
        var->name = ft_strdup(name);
        var->value = ft_strdup(value);
        free(name);
        free(value);
    }
    return (0);
}
