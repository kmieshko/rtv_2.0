/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addit_for_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 17:08:46 by kmieshko          #+#    #+#             */
/*   Updated: 2018/10/25 17:08:48 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_free(void **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}

void	move_position(char **position)
{
	char	*pos;

	pos = *position;
	while (ft_isspace(*pos))
		pos++;
	if (*pos != '{')
		ft_error("Missing '}'");
	*position = pos;
}

void	find_next_figure_bracket(char **position)
{
	char	*pos;

	pos = *position;
	while (*pos != '}')
	{
		if (!*pos)
			ft_error(" end of block '}' not found");
		pos++;
	}
	pos++;
	*position = pos;
}

void	ft_set_vector_value(t_vector *vector, char *arr)
{
	char		**res;

	res = ft_strsplit(arr, ',');
	vector->x = ft_atod(res[0]);
	vector->y = ft_atod(res[1]);
	vector->z = ft_atod(res[2]);
	ft_free((void **)res);
}

void	check_vector(t_vector vec, char *value)
{
	int		flag;

	flag = 0;
	if (vec.x < -1000 || vec.x > 1000)
		flag = 1;
	if (vec.y < -1000 || vec.y > 1000)
		flag = 1;
	if (vec.z < -1000 || vec.z > 1000)
		flag = 1;
	if (flag == 1)
	{
		ft_putstr("Error: ");
		ft_putstr(value);
		ft_putendl("out of bounds");
		exit(0);
	}
}
