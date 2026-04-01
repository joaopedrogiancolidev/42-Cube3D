#include "parser.h"

/*
** Emits missing-element error for one key if its value is NULL.
** Used by validate_required_elements() to keep checks compact.
*/
static int	print_missing_if_null(char *value, const char *key)
{
	if (!value)
	{
		parser_error_missing(key);
		return (1);
	}
	return (0);
}

/*
** Parses one RGB component from [0,255], allowing surrounding spaces/tabs.
** Used by parse_rgb_triplet() to decode F/C mandatory color fields.
*/
static int	parse_rgb_component(const char **p, int *out)
{
	int	value;

	while (**p == ' ' || **p == '\t')
		(*p)++;
	if (**p < '0' || **p > '9')
		return (1);
	value = 0;
	while (**p >= '0' && **p <= '9')
	{
		value = (value * 10) + (**p - '0');
		(*p)++;
	}
	while (**p == ' ' || **p == '\t')
		(*p)++;
	if (value < 0 || value > 255)
		return (1);
	*out = value;
	return (0);
}

/*
** Parses strict RGB syntax: n,n,n with each component in [0,255].
** Accepts trailing whitespace/newline only after third component.
*/
static int	parse_rgb_triplet(char *raw, int rgb[3])
{
	const char	*p;

	p = raw;
	if (parse_rgb_component(&p, &rgb[0]))
		return (1);
	if (*p != ',')
		return (1);
	p++;
	if (parse_rgb_component(&p, &rgb[1]))
		return (1);
	if (*p != ',')
		return (1);
	p++;
	if (parse_rgb_component(&p, &rgb[2]))
		return (1);
	while (*p == ' ' || *p == '\t' || *p == '\n')
		p++;
	return (*p != '\0');
}

/*
** Validates one color key and stores parsed RGB in parser config.
*/
static int	validate_rgb_value(char *raw, const char *key, int rgb[3])
{
	if (parse_rgb_triplet(raw, rgb) != 0)
	{
		parser_error_invalid_rgb(key);
		return (1);
	}
	return (0);
}

/*
** Builds "<dir_of_source>/<texture_path>" for relative texture paths.
** Returns NULL on allocation failure.
*/
static char	*build_source_relative_path(const char *source_path,
		const char *texture_path)
{
	const char	*last_slash;
	int			dir_len;
	char		*resolved;

	if (!source_path || texture_path[0] == '/')
		return (NULL);
	last_slash = ft_strrchr(source_path, '/');
	if (!last_slash)
		dir_len = 1;
	else if (last_slash == source_path)
		dir_len = 1;
	else
		dir_len = (int)(last_slash - source_path);
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

/*
** Validates that one texture path is non-empty and can be opened for reading.
** If the original path cannot be opened but a source-relative variant exists,
** the config is updated to store the resolved path so runtime code can use it.
*/
static int	validate_texture_path(char **path_ref, const char *key,
		const char *source_path)
{
	int		fd;
	char	*resolved;
	char	*path;

	path = *path_ref;
	if (!path || path[0] == '\0')
	{
		parser_error_invalid_texture(key, "<empty>");
		return (1);
	}
	fd = open(path, O_RDONLY);
	if (fd >= 0)
	{
		close(fd);
		return (0);
	}
	resolved = build_source_relative_path(source_path, path);
	if (!resolved)
	{
		parser_error_invalid_texture(key, path);
		return (1);
	}
	fd = open(resolved, O_RDONLY);
	if (fd < 0)
	{
		free(resolved);
		parser_error_invalid_texture(key, path);
		return (1);
	}
	/* update stored path to the resolved one for runtime usage */
	free(*path_ref);
	*path_ref = resolved;
	close(fd);
	return (0);
}

/*
** Day 2 post-parse validation for required config keys.
** Called by load_file_lines() after the file has been read.
*/
int	validate_required_elements(t_parser_config *cfg, const char *source_path)
{
	int	has_error;

	has_error = 0;
	has_error |= print_missing_if_null(cfg->no_path, "NO");
	has_error |= print_missing_if_null(cfg->so_path, "SO");
	has_error |= print_missing_if_null(cfg->we_path, "WE");
	has_error |= print_missing_if_null(cfg->ea_path, "EA");
	has_error |= print_missing_if_null(cfg->f_raw, "F");
	has_error |= print_missing_if_null(cfg->c_raw, "C");
	if (!has_error)
	{
		has_error |= validate_texture_path(&cfg->no_path, "NO", source_path);
		has_error |= validate_texture_path(&cfg->so_path, "SO", source_path);
		has_error |= validate_texture_path(&cfg->we_path, "WE", source_path);
		has_error |= validate_texture_path(&cfg->ea_path, "EA", source_path);
	}
	if (!has_error)
	{
		has_error |= validate_rgb_value(cfg->f_raw, "F", cfg->floor_rgb);
		has_error |= validate_rgb_value(cfg->c_raw, "C", cfg->ceiling_rgb);
	}
	return (has_error);
}