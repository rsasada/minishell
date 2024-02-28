/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:47:54 by jongykim          #+#    #+#             */
/*   Updated: 2024/02/29 01:33:02 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*create_var_name(const char *value, int *i, int *var_len)
{
	int		var_name_start;
	char	*ret;

	*var_len = 0;
	var_name_start = *i + 1;
	while (ft_isalnum(value[var_name_start + *var_len]) || \
	value[var_name_start + *var_len] == '_')
		(*var_len)++;
	ret = malloc(sizeof(char) * (*var_len + 1));
	if (!ret)
		exit_with_error("malloc");
	ft_strlcpy(ret, value + var_name_start, *var_len + 1);
	return (ret);
}

static void	replace_with_env(char *var_value, char **result, int *len)
{
	size_t	var_value_len;

	var_value_len = ft_strlen(var_value);
	result = ft_realloc(result, *len + var_value_len + 1);
	if (!result)
		exit_with_error("malloc");
	ft_strlcpy(*result + *len, var_value, var_value_len + 1);
	*len += var_value_len;
}

static void	handle_var_value(char **var_value, char **result, int *len)
{
	if (*var_value)
	{
		replace_with_env(*var_value, result, len);
		if (!*result)
			return ;
	}
	else
	{
		*result = ft_realloc(*result, *len + 1);
		if (!*result)
			exit_with_error("malloc");
		(*result)[*len] = '\0';
		*len += 1;
	}
}

char	*expand_env_helper(t_app *app, const char *value, int *i, int *len)
{
	t_list	*env_node;
	char	*var_name;
	char	*var_value;
	char	*result;
	int		var_len;

	result = NULL;
	var_name = create_var_name(value, i, &var_len);
	if (!var_name)
		return (NULL);
	env_node = find_env(&app->env_lst, var_name);
	if (env_node)
		var_value = ((t_env *) env_node->content)->value;
	else
		var_value = "";
	handle_var_value(&var_value, &result, len);
	free(var_name);
	*i += var_len;
	return (result);
}
