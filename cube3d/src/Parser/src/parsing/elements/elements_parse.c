/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:07:27 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/07 21:50:41 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

static int	set_element_value(char **dst, char *value, const char *key,
		int line_no)
{
	char	*clean_value;

	if (*dst)
	{
		parser_error_duplicate(key, line_no);
		return (1);
	}
	clean_value = ft_strtrim(value, " \t\n");
	if (!clean_value)
	{
		parser_error_malloc(key, line_no);
		return (1);
	}
	*dst = clean_value;
	return (0);
}

static int	handle_texture_elements(t_parser_config *cfg, char *start,
			int line_no)
{
	char	*value;

	if (ft_strncmp(start, "NO ", 3) == 0)
	{
		value = skip_spaces(start + 3);
		return (set_element_value(&cfg->no_path, value, "NO", line_no));
	}
	if (ft_strncmp(start, "SO ", 3) == 0)
	{
		value = skip_spaces(start + 3);
		return (set_element_value(&cfg->so_path, value, "SO", line_no));
	}
	if (ft_strncmp(start, "WE ", 3) == 0)
	{
		value = skip_spaces(start + 3);
		return (set_element_value(&cfg->we_path, value, "WE", line_no));
	}
	if (ft_strncmp(start, "EA ", 3) == 0)
	{
		value = skip_spaces(start + 3);
		return (set_element_value(&cfg->ea_path, value, "EA", line_no));
	}
	return (-1);
}

static int	handle_color_elements(t_parser_config *cfg, char *start,
			int line_no)
{
	char	*value;

	if (ft_strncmp(start, "F ", 2) == 0)
	{
		value = skip_spaces(start + 2);
		return (set_element_value(&cfg->f_raw, value, "F", line_no));
	}
	if (ft_strncmp(start, "C ", 2) == 0)
	{
		value = skip_spaces(start + 2);
		return (set_element_value(&cfg->c_raw, value, "C", line_no));
	}
	return (-1);
}

int	parse_element_line(t_parser_config *cfg, char *line, int line_no)
{
	char	*start;
	int		result;

	start = skip_spaces(line);
	result = handle_texture_elements(cfg, start, line_no);
	if (result != -1)
		return (result);
	result = handle_color_elements(cfg, start, line_no);
	if (result != -1)
		return (result);
	return (1);
}
