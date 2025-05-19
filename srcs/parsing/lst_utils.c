/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:13:08 by tnolent           #+#    #+#             */
/*   Updated: 2025/05/19 12:53:28 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*initialisation(void)
{
	t_list	*liste;

	liste = malloc(sizeof(*liste));
	if (liste == NULL)
		exit(0);
	liste->first = NULL;
	liste->next_list = NULL;
	liste->cmd = 0;
	return (liste);
}

int		add_token(t_list *liste, char *token, t_token *t_token)
{
	t_element	*nouveau;
	t_element	*actuel;

	nouveau = malloc(sizeof(*nouveau));
	if (!nouveau)
		return (-1);
	nouveau->next = NULL;
	nouveau->arg = ft_strdup(t_token->split->str);
	nouveau->token = token;
	nouveau->position = t_token->position;
	nouveau->env_context = 0;
	if (liste->first == NULL)
		liste->first = nouveau;
	else
	{
		actuel = liste->first;
		while (actuel->next != NULL)
			actuel = actuel->next;
		actuel->next = nouveau;	
	}
	return (1);
}

void	insertion_list(t_list *liste)
{
	t_list	*new_list;
	t_list	*current;

	new_list = malloc(sizeof(*new_list));
	if (!new_list)
	{
		free_list(liste);
		exit(0);
	}
	new_list->next_list = NULL;
	new_list->first = NULL;
	new_list->cmd = 0;
	if (liste->next_list == NULL)
		liste->next_list = new_list;
	else
	{
		current = liste->next_list;
		while (current->next_list != NULL)
			current = current->next_list;
		current->next_list = new_list;	
	}
}

void	free_list(t_list *liste)
{
	t_element	*asupprimer;
	t_list		*lst_asupprimer;

	if (liste == NULL)
		exit(EXIT_FAILURE);
	while (liste != NULL)
	{		
		while (liste->first != NULL)
		{
			if (liste->first->arg != NULL)
            {
			   free(liste->first->arg);
               liste->first->arg = NULL;
            }
			asupprimer = liste->first;
			liste->first = liste->first->next;
			free(asupprimer);
		}
		lst_asupprimer = liste;
		liste = liste->next_list;
		free(lst_asupprimer);
	}
    free(liste);
}

void	afficherliste(t_list *liste)
{
	t_element	*actuel;
	int			i;

	if (liste == NULL)
		exit(0);
	i = 0;
	while (liste != NULL)
	{		
		actuel = liste->first;
		printf("liste [%d]\n", i++);
		while (actuel != NULL)
		{
			printf("[%d]=[%s]-[%s] \n", actuel->position, actuel->arg, actuel->token);
			// printf("is in quote = [%d]\n", actuel->is_in_quotes);
			actuel = actuel->next;
		}
		liste = liste->next_list;
	}
}
