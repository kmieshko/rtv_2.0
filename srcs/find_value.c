/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 17:05:43 by kmieshko          #+#    #+#             */
/*   Updated: 2018/10/25 17:05:45 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	ft_count_coord(char *str)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count == 2)
		return (1);
	return (0);
}

static void	ft_check_needle(char *position, char *needle)
{
	int		j;
	char	*temp;
	char	*merge_str;

	j = 0;
	while (position[j] != '}' && position[j])
		j++;
	temp = ft_strnew(j);
	j = 0;
	while (position[j] != '}' && position[j])
	{
		temp[j] = position[j];
		j++;
	}
	merge_str = join(ft_strdup("\n"), needle);
	if (ft_strstr(temp, merge_str) == NULL)
		ft_error_missing_in_block(needle, temp, merge_str);
	else
	{
		ft_strdel(&merge_str);
		ft_strdel(&temp);
	}
}

char 	*ft_find_coord(char *res, char *position, char *needle)
{
	char	**tmp;
	char	**arr;
	int		i;

	i = 0;
	position++;
	ft_check_needle(position, needle);
	arr = ft_strsplit(position, '\n');
	while (arr[i] && ft_strcmp(arr[i], "}") != 0)
	{
		tmp = ft_strsplit(arr[i], ':');
		if (tmp[0] && tmp[1])
		{
			if (ft_strcmp(tmp[0], needle) == 0)
			{
				if (ft_count_coord(tmp[1]))
					res = ft_strcpy(res, tmp[1]);
				else
				{
					char *str1 = join(ft_strdup("wrong camera's "), needle);
					char *str2 = join(str1, " parameters");
					ft_error(str2);
				}
			}
		}
		else if (tmp[0] && !tmp[1])
		{
			ft_error(join(ft_strdup("missing value after "), tmp[0]));
		}
		ft_free((void **)tmp);
		i++;
	}
	ft_free((void **)arr);
	return (res);
}

char 	*ft_find_value(char *res, char *position, char *needle)
{
	char	**tmp;
	char	**arr;
	int		i;

	i = 0;
	position++;
	ft_check_needle(position, needle);
	arr = ft_strsplit(position, '\n');
	while (arr[i] && ft_strcmp(arr[i], "}") != 0)
	{
		tmp = ft_strsplit(arr[i], ':');
		if (tmp[0] && tmp[1])
		{
			if (ft_strcmp(tmp[0], needle) == 0)
				res = ft_strcpy(res, tmp[1]);
		}
		else if (tmp[0] && !tmp[1])
		{
			ft_error(join(ft_strdup("missing value after "), tmp[0]));
		}
		ft_free((void **)tmp);
		i++;
	}
	ft_free((void **)arr);
	return (res);
}
