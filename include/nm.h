/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm-otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 18:48:32 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/02 14:09:15 by thifranc         ###   ########.fr       */
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

#define OPT_R 1
#define OPT_P 2
#define OPT_N 4
#define OPT_U 8
#define OPT_J 16
#define TO_SWAP 32
#define IS_32 64

#define N_SECT_MASK 1024

typedef struct s_a {
	unsigned char	opt;
	unsigned char	n_sect;
	unsigned char	data_sec;
	unsigned char	text_sec;
	unsigned char	bss_sec;
} t_a;

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <ar.h>

# define DEBUG dprintf(1, "- %s - %s\n" \
		, __FILE__, __FUNCTION__);

int		handle_error(int flag);
int		handle_macho(char *file, t_a g);
int		handle_64(char *title, char *ptr, t_a g);
int		handle_32(char *title, char *ptr, t_a g);

int		parser(int ac, char **av);

char	*get_type(int type, t_a g);
void	utils_match_nsect(char *segname, char *sectname, t_a *g, int cur);
void	printBits(size_t const size, void const * const ptr);

#endif
