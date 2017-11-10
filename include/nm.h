/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm-otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 18:48:32 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/10 16:44:17 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

#define ERR_MULTI_OPT 128
#define ERR_SAME_ARG 129
#define ERR_OPEN 1
#define ERR_FSTAT 2
#define ERR_MMAP 4
#define ERR_MAGIC 8
#define ERR_MALLOC 16
#define ERR_IS_COMPROMISED 32
#define ERR_IS_FAT 64

#define OPT_R 1
#define OPT_P 2
#define OPT_N 4
#define OPT_U 8
#define OPT_J 16
#define TO_SWAP 32
#define IS_32 64

#define N_SECT_MASK 1024


typedef struct s_a {
	int				filesize;
	int				nsyms;
	unsigned char	opt;
	unsigned char	n_sect;
	unsigned char	data_sec;
	unsigned char	text_sec;
	unsigned char	bss_sec;
	char			*title;
} t_a;

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include <ar.h>

# define DEBUG dprintf(1, "- %s - %s\n" \
		, __FILE__, __FUNCTION__);

void	quickSort(char ***arr, int low, int high, t_a g);

int		handle_error(int flag);
int		is_compromised(long size, long start, long jump, long offset);

int		handle_fat(char *ptr, t_a g);
int		handle_macho(char *file, t_a g);
int		handle_64(char *ptr, t_a g);
int		handle_32(char *ptr, t_a g);

int		parser(int ac, char **av);

void	utils_match_nsect(char *segname, char *sectname, t_a *g, int cur);
void	printBits(size_t const size, void const * const ptr);

void	print_tab(char **tab, int len);
long long unsigned		swaptest(long long int a, char options);
long long unsigned		swap_bits(long long int num);

struct load_command	swap_lc(struct load_command *lc, char opt);

struct nlist	swap_st(struct nlist st, char opt);
struct symtab_command	swap_sc(struct symtab_command *sc, char opt);

struct nlist_64	swap_st_64(struct nlist_64 st, char opt);
struct symtab_command_64	swap_sc_64(struct symtab_command_64 *sc, char opt);
#endif
