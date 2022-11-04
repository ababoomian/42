#include "./minishell.h"

char *get_expand(char *str, t_env **node)
{
	char *res;

	res = find_val_by_key(node,++str);
	return (res);
}