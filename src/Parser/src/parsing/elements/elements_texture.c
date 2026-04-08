/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 21:10:20 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/07 22:19:48 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_dir_len(const char *source_path, const char **last_slash)
{
	*last_slash = ft_strrchr(source_path, '/');
	if (!*last_slash || *last_slash == source_path)
		return (1);
	return ((int)(*last_slash - source_path));
}

static int	try_open_texture(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

static int	report_texture_error(const char *key, char *path)
{
	parser_error_invalid_texture(key, path);
	return (1);
}

static char	*build_source_relative_path(const char *source_path,
			const char *texture_path)
{
	const char	*last_slash;
	int			dir_len;
	char		*resolved;

	if (!source_path || texture_path[0] == '/')
		return (NULL);
	dir_len = get_dir_len(source_path, &last_slash);
	resolved = (char *)malloc(sizeof(char) * (dir_len + 1
				+ (int)ft_strlen(texture_path) + 1));
	if (!resolved)
		return (NULL);
	if (!last_slash)
		resolved[0] = '.';
	else
		ft_memcpy(resolved, source_path, dir_len);
	resolved[dir_len] = '/';
	ft_memcpy(resolved + dir_len + 1, texture_path, ft_strlen(texture_path));
	resolved[dir_len + 1 + (int)ft_strlen(texture_path)] = '\0';
	return (resolved);
}

int	validate_texture_path(char **path_ref, const char *key,
			const char *source_path)
{
	char	*resolved;
	char	*path;

	path = *path_ref;
	if (!path || path[0] == '\0')
	{
		parser_error_invalid_texture(key, "<empty>");
		return (1);
	}
	if (try_open_texture(path) == 0)
		return (0);
	resolved = build_source_relative_path(source_path, path);
	if (!resolved)
		return (report_texture_error(key, path));
	if (try_open_texture(resolved) != 0)
	{
		free(resolved);
		return (report_texture_error(key, path));
	}
	free(*path_ref);
	*path_ref = resolved;
	return (0);
}
