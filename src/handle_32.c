/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:40:59 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/02 13:43:49 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

void	symtab_32(struct symtab_command *sc, char *ptr, t_a g)
{
	DEBUG
	struct	nlist	*symbol_table;
	char			*stringtable;
	char			*address;
	int				type;
	int				j;

	j = 0;
	symbol_table = (void *)ptr + sc->symoff;
	stringtable = (void *)ptr + sc->stroff;
	while (j < (int)sc->nsyms)
	{
		
		address = symbol_table[j].n_value ?
			ft_ptrf("%0*x", symbol_table[j].n_value, 8) :
			"        ";

		type = symbol_table[j].n_type & N_TYPE;

		ft_putstr(ft_ptrf("%s %s %s\n", address, get_type(type, g), stringtable
				+ symbol_table[j].n_un.n_strx));
		j++;
	}
}

int		handle_32(char *title, char *ptr, t_a g)
{
	DEBUG
		struct	mach_header		*header;
	struct	load_command	*lc;
	int						i;

	dprintf(1, "%s, %d\n", title, g.opt);
	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(struct mach_header);

	i = 0;
	while (i < (int)header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			symtab_32((struct symtab_command *)lc, ptr, g);
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return (0);

}
