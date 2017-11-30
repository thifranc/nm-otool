/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm-otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 18:48:32 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/30 16:51:01 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach/machine.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include <ar.h>

# define ERR_OPEN			1
# define ERR_FSTAT			2
# define ERR_MMAP			4
# define ERR_MAGIC			8
# define ERR_MALLOC			16
# define ERR_IS_COMPROMISED 32
# define ERR_NO_ARG			64
# define ERR_MULTI_OPT		4096

# define OPT_D				1
# define TO_SWAP			32
# define IS_32				64
# define MANY_ARGS			128

# define IS_FAT				256
# define NO_X86_64			512
# define MANY_ARCHS			1024
# define HAS_ONE_ERROR		2048
# define IS_LIB				4096

# define N_SECT_MASK		1024

typedef struct				s_a
{
	int				filesize;
	int				nsyms;
	int				opt;
	unsigned char	n_sect;
	unsigned char	data_sec;
	unsigned char	text_sec;
	unsigned char	bss_sec;
	char			*title;
	char			*cputype;
	char			**output;
}							t_a;

void						quick_sort(char ***arr, int low, int high, t_a g);

int							handle_error(int flag, char *filename);
int							is_compromised(
								long size, long start, long jump, long offset);

int							handle_fat(char *ptr, t_a *g);
int							handle_macho(char *file, t_a *g);
int							handle_64(char *ptr, t_a *g);
int							handle_32(char *ptr, t_a *g);

int							parser(int ac, char **av);

void						print_bits(int size, void *ptr);

void						print_tab(char **tab, struct s_a g);
long long unsigned			swaptest(long long int a, char options);
long long unsigned			swap_bits(long long int num);

struct load_command			swap_lc(struct load_command *lc, char opt);

struct nlist				swap_st(struct nlist st, char opt);
struct symtab_command		swap_sc(struct symtab_command *sc, char opt);

struct nlist_64				swap_st_64(struct nlist_64 st, char opt);
struct symtab_command_64	swap_sc_64(struct symtab_command_64 *sc, char opt);

char						*get_cpu_string(int cputype);
void						init_g_struct(t_a *g);
char						get_type(int type, t_a g, int fallback);

int							handle_lc(struct load_command lc_clean,
							struct load_command *lc, t_a *g, char *ptr);

void						free_tab(char ***tab, int len);

int							handle_lib(void *ptr, t_a *g);
void						print_ppc_style(int size,
								int offset, int addr, char *ptr);
void						print_title(t_a g, char *sectname, char *segname);
#endif
