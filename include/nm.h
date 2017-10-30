/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm-otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 18:48:32 by thifranc          #+#    #+#             */
/*   Updated: 2017/10/30 16:18:42 by thifranc         ###   ########.fr       */
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

#define OPT_R 1
#define OPT_P 2
#define OPT_N 4
#define OPT_U 8
#define OPT_J 16
#define TO_SWAP 32
#define IS_32 64

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

int		parser(int ac, char **av);
void	printBits(size_t const size, void const * const ptr);
int		handle_error(int flag);
int		handle_macho(char *file, int options);
int		handle_64(char *title, char *ptr, int options);
int		handle_32(char *title, char *ptr, int options);
char	*get_type(int type);

#endif
