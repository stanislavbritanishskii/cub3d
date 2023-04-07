/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhendzel <dhendzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:25:31 by sbritani          #+#    #+#             */
/*   Updated: 2023/04/07 23:53:49 by dhendzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

t_dict	*init_dict(void)
{
	t_dict	*res;

	res = malloc(sizeof(t_dict));
	res->keys = malloc(sizeof(char *));
	res->values = malloc(sizeof(char *));
	res->values[0] = NULL;
	res->keys[0] = NULL;
	res->len = 0;
	return (res);
}

void	dict_add(t_dict *dict, char *key, char *value)
{
	int	i;

	i = 0;
	while (dict->keys[i] && !strings_equal(dict->keys[i], key))
		i++;
	if (!dict->keys[i])
	{
		dict->keys = add_string_to_string_arr(key, dict->keys, dict->len);
		dict->values = add_string_to_string_arr(value, dict->values, dict->len);
		dict->len++;
	}
	else
	{
		free(dict->values[i]);
		dict->values[i] = str_copy(value, -1);
	}
}

char	*dict_get(t_dict *dict, char *key, char *default_return)
{
	int	i;

	i = 0;
	while (i < dict->len && !strings_equal(dict->keys[i], key))
		i++;
	if (dict->keys[i])
		return (dict->values[i]);
	return (default_return);
}

void	dict_delete(t_dict *dict, char *key)
{
	int	i;

	i = 0;
	while (dict->keys[i] && !strings_equal(dict->keys[i], key))
		i++;
	if (i < dict->len)
	{
		dict->keys = remove_string_from_str_arr(dict->keys, i);
		dict->values = remove_string_from_str_arr(dict->values, i);
		dict->len--;
	}
}

void	free_dict(t_dict *dict)
{
	int	i;

	i = 0;
	while (i < dict->len)
	{
		free(dict->keys[i]);
		if (dict->values[i])
			free(dict->values[i]);
		i++;
	}
	free(dict->keys);
	free(dict->values);
	free(dict);
}
