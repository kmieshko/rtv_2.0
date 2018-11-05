/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmieshko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 17:09:32 by kmieshko          #+#    #+#             */
/*   Updated: 2018/10/25 17:09:33 by kmieshko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_error(char *str)
{
	ft_putstr("Error: ");
	ft_putendl(str);
	exit(0);
}

void	ft_error_missing_in_block(char *needle, char *temp, char *merge_str)
{
	ft_putstr("missing ");
	ft_putstr(needle);
	ft_putstr(" in block:\n{");
	ft_putstr(temp);
	ft_putendl("}");
	ft_strdel(&merge_str);
	ft_strdel(&temp);
	exit(0);
}
