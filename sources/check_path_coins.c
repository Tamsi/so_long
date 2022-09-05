/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_coins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamsi <tamsi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 19:16:37 by tamsi             #+#    #+#             */
/*   Updated: 2022/09/05 19:38:10 by tamsi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_map	create_new_map(t_map map)
{
	t_map	new_map;
	int		i;

	i = -1;
	new_map.coins = map.coins;
	new_map.columns = map.columns;
	new_map.rows = map.rows;
	new_map.full = malloc((map.rows + 1) * sizeof(char *));
	while (++i < map.rows)
		new_map.full[i] = ft_strdup(map.full[i]);
	return (new_map);
}

static void	ft_free_new_map(t_map map)
{
	int	string;

	string = 0;
	while (string < map.rows)
		free(map.full[string++]);
	free(map.full);
}

static int check_coins(t_map map, int i, int j, int **visited)
{
	int	up;
	int	left;
	int	down;
	int	right;

	if (is_safe(i, j, map) && map.full[i][j] != '1' && !visited[i][j])
	{
		visited[i][j] = 1;
		if (map.coins == 1)
			return (1);
		if (map.full[i][j] == 'C')
		{
			map.full[i][j] = '0';
			map.coins--;
		}
		up = check_coins(map, i - 1, j, visited);
		if (up)
			return (1);
		left = check_coins(map, i, j - 1, visited);
		if (left)
			return (1);
		down = check_coins(map, i + 1, j, visited);
		if (down)
			return (1);
		right = check_coins(map, i, j + 1, visited);
		if (right)
			return (1);
	}
	return (0);
}

int	search_path_coins(t_game *game)
{
	int		**visited;
	t_map	new_map;
	int		i;
	int		j;
	int		flag;

	visited = create_visited(game->map);
	new_map = create_new_map(game->map);
	i = 0;
	flag = 0;
	while (i < new_map.rows)
	{
		j = 0;
		while (j < new_map.columns)
		{
			if (new_map.full[i][j] == 'P' && visited[i][j] == 0)
				if (check_coins(new_map, i, j, visited))
				{
					flag = 1;
					break;
				}
			j++;
		}
		i++;
	}
	ft_free_new_map(new_map);
	free_visited(visited, game->map);
	return (flag);
}
