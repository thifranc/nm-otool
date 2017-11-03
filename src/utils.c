/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 12:46:07 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/03 09:46:54 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

void	utils_match_nsect(char *segname, char *sectname, t_a *g, int cur)
{
	if (ft_strcmpi(segname, sectname) == 0)
	{
		if (!ft_strcmp(sectname, "__data"))
			g->data_sec = g->n_sect + cur + 1;
		else if (!ft_strcmp(sectname, "__text"))
		{
			g->text_sec = g->n_sect + cur + 1;
		}
		else if (!ft_strcmp(sectname, "__bss"))
			g->bss_sec = g->n_sect + cur + 1;
	}
}

char	*get_type(int type, t_a g)
{
	char	*n_type;

	if (type & N_SECT_MASK)
	{
		type = type ^ N_SECT_MASK;
		if (type == g.bss_sec)
			n_type =  "B";
		else if (type == g.data_sec)
			n_type =  "D";
		else if (type == g.text_sec)
			n_type =  "T";
	}
	if (type == N_UNDF || type == N_PBUD)
		n_type = "U";
	if (type == N_ABS)
		n_type = "A";
	return (n_type);
}
