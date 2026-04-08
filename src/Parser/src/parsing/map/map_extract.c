/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:31:36 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/07 23:24:15 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_max_map_width(t_map_grid *map)
{
	int	i;
	int	max_width;
	int	line_len;

	i = 0;
	max_width = 0;
	while (i < map->height)
	{
		line_len = (int)ft_strlen(map->lines[i]);
		if (line_len > max_width)
			max_width = line_len;
		i++;
	}
	return (max_width);
}

static int	normalize_line(char **dst, char *src, int width)
{
	int	line_len;

	*dst = (char *)malloc(sizeof(char) * (width + 1));
	if (!*dst)
		return (1);
	ft_memset(*dst, ' ', width);
	line_len = (int)ft_strlen(src);
	if (line_len > 0)
		ft_memcpy(*dst, src, line_len);
	(*dst)[width] = '\0';
	return (0);
}

static void	free_partial_normalized(char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

static int	build_normalized_grid(t_map_grid *map, char ***normalized_out)
{
	char	**normalized;
	int		i;

	map->width = get_max_map_width(map);
	if (map->height == 0 || map->width == 0)
		return (0);
	normalized = (char **)malloc(sizeof(char *) * map->height);
	if (!normalized)
		return (1);
	i = 0;
	while (i < map->height)
	{
		if (normalize_line(&normalized[i], map->lines[i], map->width))
		{
			free_partial_normalized(normalized, i);
			return (1);
		}
		i++;
	}
	*normalized_out = normalized;
	return (0);
}

int	extract_map_grid(t_map_grid *map)
{
	char	**normalized;
	int		result;
	int		i;

	result = build_normalized_grid(map, &normalized);
	if (result != 0 || map->height == 0 || map->width == 0)
		return (result);
	i = 0;
	while (i < map->height)
	{
		free(map->lines[i]);
		i++;
	}
	free(map->lines);
	map->lines = normalized;
	return (0);
}
