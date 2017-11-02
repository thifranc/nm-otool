/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:40:59 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/02 17:14:29 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

int		symtab_32(struct symtab_command *sc, char *ptr, t_a g)
{
	DEBUG
	struct	nlist	*symbol_table;
	char			*stringtable;
	char			*address;
	int				type;
	int				j;

	j = 0;
	if (!is_compromised(g.filesize, 0, 0, sc->symoff) &&
			!is_compromised(g.filesize, 0, 0, sc->stroff))
	{
		symbol_table = (void *)ptr + sc->symoff;
		stringtable = (void *)ptr + sc->stroff;
	}
	else
		return (ERR_IS_COMPROMISED);
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
	return (0);
}

int		handle_32(char *ptr, t_a g)
{
	DEBUG
	struct	mach_header		*header;
	struct	load_command	*lc;
	int						i;
	int						error;

	error = 0;
	header = (struct mach_header *)ptr;
	if (!is_compromised(g.filesize, 0, 0, sizeof(struct mach_header)))
		lc = (void *)ptr + sizeof(struct mach_header);
	else
		error = ERR_IS_COMPROMISED;

	i = 0;
	while (i < (int)header->ncmds && !error)
	{
		if (lc->cmd == LC_SYMTAB)
			error = symtab_32((struct symtab_command *)lc, ptr, g);
		if (!is_compromised(g.filesize, (int)ptr, (int)((void*)lc + lc->cmdsize), 0))
			lc = (void *)lc + lc->cmdsize;
		else
			error = ERR_IS_COMPROMISED;
		i++;
	}
	return (0);
}
