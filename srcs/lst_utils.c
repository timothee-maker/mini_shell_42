/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:13:08 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/03 16:19:48 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*initialisation(void);
void	afficherliste(t_list *liste);
void	insertion_f(t_list *liste, char *arg, char *token, int index);
void	destruction(t_list *liste);

t_list	*initialisation(void)
{
	t_list	*liste;

	liste = malloc(sizeof(*liste));
	if (liste == NULL)
		exit(0);
	liste->first = NULL;
	return (liste);
}

void	insertion_f(t_list *liste, char *arg, char *token, int index)
{
	t_element	*nouveau;
	t_element	*actuel;

	nouveau = malloc(sizeof(*nouveau));
	if (liste == NULL || nouveau == NULL)
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

void	destruction(t_list *liste)
{
	t_element	*asupprimer;

	if (liste == NULL)
		exit(EXIT_FAILURE);
	while (liste->first != NULL)
	{
		free(liste->first->arg);
		asupprimer = liste->first;
		liste->first = liste->first->next;
		free(asupprimer);
	}
}

void	afficherliste(t_list *liste)
{
	t_element	*actuel;

	if (liste == NULL)
		exit(0);
	actuel = liste->first;
	while (actuel != NULL)
	{
		printf("position[%d]=[%s]-[%s] \n", actuel->position, actuel->arg, actuel->token);
		actuel = actuel->next;
	}
}