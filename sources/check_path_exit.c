/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:44:37 by tamsi             #+#    #+#             */
/*   Updated: 2022/09/05 19:39:43 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int check_path(t_map map, int i, int j, int **visited)
{
	int	up;
	int	left;
	int	down;
	int	right;

	if (is_safe(i, j, map) && map.full[i][j] != '1' && !visited[i][j])
	{
		visited[i][j] = 1;
		if (map.full[i][j] == 'E')
			return (1);
		up = check_path(map, i - 1, j, visited);
		if (up)
			return (1);
		left = check_path(map, i, j - 1, visited);
		if (left)
			return (1);
		down = check_path(map, i + 1, j, visited);
		if (down)
			return (1);
		right = check_path(map, i, j + 1, visited);
		if (right)
			return (1);
	}
	return (0);
}

int	search_path_exit(t_game *game)
{
	int	**visited;
	int	i;
	int	j;
	int	flag;

	visited = create_visited(game->map);
	flag = 0;
	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (j < game->map.columns)
		{
			if (game->map.full[i][j] == 'P' && visited[i][j] == 0)
				if (check_path(game->map, i, j, visited))
				{
					flag = 1;
					break;
				}
			j++;
		}
		i++;
	}
	free_visited(visited, game->map);
	return (flag);
}
