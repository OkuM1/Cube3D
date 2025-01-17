/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:43:55 by mokutucu          #+#    #+#             */
/*   Updated: 2025/01/17 14:15:56 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr) 
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	rgba_int(int r, int g, int b, int a)
{
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

int	space_counter(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t') 
		i++;
	return (i);
}

char	*remove_newline(char *string)
{
	int	i;

	i = 0;
	while (string[i] && string[i] != '\n')
		i++;
	if (string[i] == '\n')
		string [i] = '\0';
	return (string);
}
