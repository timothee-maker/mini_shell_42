/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:13:08 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/12 15:48:38 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*initialisation(void)
{
	t_list	*liste;

	liste = malloc(sizeof(*liste));
	if (liste == NULL)
		exit(0);
	liste->first = NULL;
	liste->next_list = NULL;
	return (liste);
}

void	insertion_element(t_list *liste, char *arg, char *token, int index)
{
	t_element	*nouveau;
	t_element	*actuel;

	nouveau = malloc(sizeof(*nouveau));
	if (!liste || !nouveau)
		exit(0);
	nouveau->next = NULL;
	nouveau->arg = arg;
	nouveau->token = token;
	nouveau->position = index;
	if (liste->first == NULL)
		liste->first = nouveau;
	else
	{
		actuel = liste->first;
		while (actuel->next != NULL)
			actuel = actuel->next;
		actuel->next = nouveau;	
	}
}

void	insertion_list(t_list *liste)
{
	t_list	*new_list;
	t_list	*current;

	new_list = malloc(sizeof(*new_list));
	if (!liste || !new_list)
		exit(0);
	new_list->next_list = NULL;
	new_list->first = NULL;
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

void	destruction(t_list *liste)
{
	t_element	*asupprimer;
	t_list		*lst_asupprimer;

	if (liste == NULL)
		exit(EXIT_FAILURE);
	while (liste != NULL)
	{		
		while (liste->first != NULL)
		{
			free(liste->first->arg);
			asupprimer = liste->first;
			liste->first = liste->first->next;
			free(asupprimer);
		}
		lst_asupprimer = liste;
		liste = liste->next_list;
		free(lst_asupprimer);
	}
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
		// printf("liste des infiles : %s, liste des outfiles : %s\n", liste->infile->token, liste->outfile->token);
		while (actuel != NULL)
		{
			printf("position[%d]=[%s]-[%s] \n", actuel->position, actuel->arg, actuel->token);
			actuel = actuel->next;
		}
		liste = liste->next_list;
	}
}
