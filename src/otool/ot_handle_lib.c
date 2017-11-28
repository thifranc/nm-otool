
#include "../../include/otool.h"

int		handle_lib(void *ptr, t_a *g)
{
	int size;
	int len;
	int offset;

	len = 0;
	size = 0;
	if (g->filesize > 68 && (size = ft_atoi(ptr + 56)) &&
		size + 68 < g->filesize)
		ptr += (size + 68);
	offset = size + 68;
	ft_putstrdel(ft_ptrf("Archive : %s\n", g->title));
	while (size > 0 && *(char*)ptr)
	{
		if (offset + 60 >= g->filesize ||
			((size = ft_atoi(ptr + 48)) + offset) >= g->filesize)
			return (ERR_IS_COMPROMISED);
		len = 8 * ((ft_strlen(ptr + 60) - 1) / 8 + 1) + 4;
		size = ft_atoi(ptr + 48);
		ft_putstrdel(ft_ptrf("%s(%s):\n", g->title, ptr + 60));
		if (handle_64(ptr + 60 + len, g) > 0)
			return (ERR_IS_COMPROMISED);
		ptr += (size + 60);
		offset += (size + 60);
	}
	return (!size ? ERR_IS_COMPROMISED : 0);
}
