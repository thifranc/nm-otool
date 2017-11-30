/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 18:45:35 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/30 15:26:41 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

struct load_command		swap_lc(struct load_command *lc, char opt)
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

struct nlist			swap_st(struct nlist st, char opt)
{
	struct nlist	st_clean;

	st_clean = st;
	st_clean.n_value = swaptest(st.n_value, opt);
	st_clean.n_un.n_strx = swaptest(st.n_un.n_strx, opt);
	return (st_clean);
}

struct nlist_64			swap_st_64(struct nlist_64 st, char opt)
{
	struct nlist_64	st_clean;

	st_clean = st;
	st_clean.n_value = swaptest(st.n_value, opt);
	st_clean.n_un.n_strx = swaptest(st.n_un.n_strx, opt);
	return (st_clean);
}

long long unsigned		swap_bits(long long int num)
{
	return (((num >> 24) & 0xff) | ((num << 8) & 0xff0000) |
			((num >> 8) & 0xff00) |
			((num << 24) & 0xff000000));
}
