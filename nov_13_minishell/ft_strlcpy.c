#include "./minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	id;

	if (!dst || !src)
		return (0);
	id = 0;
	if (dstsize != 0)
	{
		while (src[id] != '\0' && id < (dstsize - 1))
		{
			dst[id] = src[id];
			id++;
		}
		dst[id] = '\0';
	}
	return (ft_strlen(src));
}
