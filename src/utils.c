/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 12:46:07 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/04 10:21:46 by thifranc         ###   ########.fr       */
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

void	print_tab(char **tab, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		ft_putstr(tab[i]);
		i++;
	}
}

struct load_command	swap_lc(struct load_command *lc, char opt)
{
	struct load_command	lc_clean;

	lc_clean = *lc;
	lc_clean.cmd = swaptest(lc->cmd, opt);
	lc_clean.cmdsize = swaptest(lc->cmdsize, opt);
	return (lc_clean);
}

struct symtab_command	swap_sc(struct symtab_command *sc, char opt)
{
	struct symtab_command	sc_clean;

	sc_clean = *sc;
	sc_clean.symoff = swaptest(sc->symoff, opt);
	sc_clean.stroff = swaptest(sc->stroff, opt);
	sc_clean.nsyms = swaptest(sc->nsyms, opt);
	return (sc_clean);
}

struct nlist	swap_st(struct nlist st, char opt)
{
	struct nlist	st_clean;

	st_clean = st;
	st_clean.n_sect = swaptest(st.n_sect, opt);
	st_clean.n_type = swaptest(st.n_type, opt);
	st_clean.n_value = swaptest(st.n_value, opt);
	st_clean.n_un.n_strx = swaptest(st.n_un.n_strx, opt);
	return (st_clean);
}
/*
  * move byte 3 to byte 0
  * move byte 1 to byte 2
  * move byte 2 to byte 1
  * move byte 0 to byte 3
*/

int		swap_bits(int num)
{
	return ((num>>24)&0xff) |
				((num<<8)&0xff0000) |
				((num>>8)&0xff00) |
				((num<<24)&0xff000000);
}

int		swaptest(int a, char options)
{
	if (options & TO_SWAP)
		return (swap_bits(a));
	else
		return (a);
}


