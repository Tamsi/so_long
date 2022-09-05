/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 19:39:28 by tamsi             #+#    #+#             */
/*   Updated: 2022/09/05 19:41:07 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int is_safe(int i, int j, t_map map)
{
	if (i >= 1 && i < map.rows && j >= 1 && j < map.columns)
		return (1);
	return (0);
}

int	**create_visited(t_map map)
{
	int	**visited;
	int	i;
	int	j;

	i = 0;
	visited = malloc(map.rows * sizeof(int *));
	if (!visited)
		exit(-1);
	while (i < map.rows)
	{
		j = 0;
		visited[i] = malloc(map.columns * sizeof(int));
		if (!visited[i])
			exit(-1);
		while (j < map.columns)
		{
			visited[i][j] = 0;
			j++;
		}
		i++;
	}
	return (visited);
}

void	free_visited(int **visited, t_map map)
{
	int	i;

	i = 0;
	while (i < map.rows)
		free(visited[i++]);
	free(visited);
}
