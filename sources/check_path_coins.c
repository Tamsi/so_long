/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_coins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbesson <tbesson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 19:16:37 by tamsi             #+#    #+#             */
/*   Updated: 2022/09/06 16:20:13 by tbesson          ###   ########.fr       */
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

static int	check_coins(t_map map, int i, int j, int **visited)
{
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
		if (check_coins(map, i - 1, j, visited))
			return (1);
		if (check_coins(map, i, j - 1, visited))
			return (1);
		if (check_coins(map, i + 1, j, visited))
			return (1);
		if (check_coins(map, i, j + 1, visited))
			return (1);
	}
	return (0);
}

static int	parse_map(t_map new_map, int **visited)
{
	int		i;
	int		j;
	int		flag;

	flag = 0;
	i = -1;
	while (++i < new_map.rows)
	{
		j = -1;
		while (++j < new_map.columns)
		{
			if (new_map.full[i][j] == 'P' && visited[i][j] == 0)
			{
				if (check_coins(new_map, i, j, visited))
				{
					flag = 1;
					break ;
				}
			}
		}
	}
	return (flag);
}

int	search_path_coins(t_game *game)
{
	int		**visited;
	t_map	new_map;
	int		flag;

	visited = create_visited(game->map);
	new_map = create_new_map(game->map);
	flag = parse_map(new_map, visited);
	ft_free_new_map(new_map);
	free_visited(visited, game->map);
	return (flag);
}
