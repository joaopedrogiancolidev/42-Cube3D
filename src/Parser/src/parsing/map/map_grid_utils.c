/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:36:16 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/07 20:24:20 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_map_grid(t_map_grid *map)
{
	map->lines = NULL;
	map->height = 0;
	map->width = 0;
}

void	free_map_grid(t_map_grid *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->lines[i]);
		i++;
	}
	free(map->lines);
	map->lines = NULL;
	map->height = 0;
	map->width = 0;
}

static char	*dup_line_without_newline(char *line)
{
	int		len;
	char	*copy;

	len = (int)ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	if (len > 0)
		ft_memcpy(copy, line, len);
	copy[len] = '\0';
	return (copy);
}

static int	alloc_new_lines(t_map_grid *map, char *line,
			int line_no, char ***new_lines_out)
{
	char	**new_lines;
	char	*clean_line;

	clean_line = dup_line_without_newline(line);
	if (!clean_line)
	{
		parser_error_malloc("MAP", line_no);
		return (1);
	}
	new_lines = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!new_lines)
	{
		free(clean_line);
		parser_error_malloc("MAP", line_no);
		return (1);
	}
	new_lines[map->height] = clean_line;
	*new_lines_out = new_lines;
	return (0);
}

int	add_map_line(t_map_grid *map, char *line, int line_no)
{
	char	**new_lines;
	int		i;

	if (alloc_new_lines(map, line, line_no, &new_lines) != 0)
		return (1);
	i = 0;
	while (i < map->height)
	{
		new_lines[i] = map->lines[i];
		i++;
	}
	free(map->lines);
	map->lines = new_lines;
	map->height++;
	return (0);
}
