#include "../../includes/minishell.h"

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

static t_env *get_variable(char *name, t_env *env)
{
    t_env *current;
    char *dup;

    current = env;
    while (current)
    {
        dup = get_var_name(current->name);
        if (!ft_strcmp(name, dup))
        {
            free(dup);
            return (current);
        }
        free(dup);
        current = current->next;
    }
    return (NULL);
}

int ft_export(t_exec *exec, t_cmd *cmd)
{
    t_env *var;

    if (cmd->args[1] == NULL)
        return (0); // launch no args function
    else if (!valid_identifier(cmd->args[1]))
        ft_putstr_fd("export: invalid identifier\n", 2);
    else
    {
        var = get_variable(cmd->args[1], exec->env);
        if (!var)
            return (0); // init new env
        var->value = get_var_value(cmd->args[1]);
    }
}
