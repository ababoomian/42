/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrsargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 03:37:49 by vrsargsy          #+#    #+#             */
/*   Updated: 2022/11/18 03:42:09 by vrsargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./minishell.h"

void	print_list_tenv(t_env *head)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		if (current->del != 1)
			printf("%s : %s \n", current->key, current->value);
		current = current->next;
	}
}

t_env	*new_dict_tenv(char *key, char *value)
{
	t_env	*new_t_env;

	new_t_env = (t_env *)malloc(sizeof(t_env));
	if (new_t_env == NULL)
		return (NULL);
	new_t_env->key = key;
	new_t_env->value = value;
	new_t_env->del = 0;
	new_t_env->next = NULL;
	return (new_t_env);
}

t_env	*init_env_tenv(char **env)
{
	t_env	*head;
	t_env	*tmp;
	int		i;

	i = 0;
	head = new_dict_tenv(get_key_env(env[i]), get_value_env(env[i]));
	tmp = head;
	while (env[++i])
	{
		tmp->next = new_dict_tenv(get_key_env(env[i]), get_value_env(env[i]));
		tmp = tmp->next;
	}
	return (head);
}
