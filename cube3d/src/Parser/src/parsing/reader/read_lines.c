/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:17:59 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/07 15:27:53 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

typedef struct s_line_state
{
	int	has_invalid;
	int	has_map_started;
	int	line_no;
}	t_line_state;

static int	is_map_allowed_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == ' ');
}

static void	report_invalid_line(char *line, int line_no, int has_map_started)
{
	int	col;

	if (!has_map_started)
	{
		parser_error_invalid_line(line_no);
		return ;
	}
	col = 0;
	while (line[col] != '\0' && line[col] != '\n')
	{
		if (!is_map_allowed_char(line[col]))
		{
			parser_error_map_invalid_char(line_no, col + 1, line[col]);
			return ;
		}
		col++;
	}
	parser_error_invalid_line(line_no);
}

static void	process_line_content(char *line, t_parser_config *cfg_out,
		t_map_grid *map_out, t_line_state *state)
{
	char	*line_type;

	line_type = (char *)line_type_name(line);
	if (ft_strncmp(line_type, "ELEMENT", 8) == 0)
	{
		if (state->has_map_started)
		{
			state->has_invalid = 1;
			parser_error_element_after_map(state->line_no);
		}
		else if (parse_element_line(cfg_out, line, state->line_no) != 0)
			state->has_invalid = 1;
	}
	else if (ft_strncmp(line_type, "MAP", 4) == 0)
	{
		state->has_map_started = 1;
		if (add_map_line(map_out, line, state->line_no) != 0)
			state->has_invalid = 1;
	}
	else if (ft_strncmp(line_type, "INVALID", 8) == 0)
	{
		state->has_invalid = 1;
		report_invalid_line(line, state->line_no, state->has_map_started);
	}
}

static int	finalize_parsed_data(t_line_state *state,
		t_parser_config *cfg_out, t_map_grid *map_out,
		const char *source_path)
{
	if (!state->has_invalid)
		state->has_invalid = validate_required_elements(cfg_out, source_path);
	if (!state->has_invalid && extract_map_grid(map_out) != 0)
	{
		state->has_invalid = 1;
		parser_error_malloc("MAP", state->line_no);
	}
	if (!state->has_invalid && validate_map_charset_and_spawn(map_out) != 0)
		state->has_invalid = 1;
	if (!state->has_invalid && validate_map_closed(map_out) != 0)
		state->has_invalid = 1;
	if (state->has_invalid)
	{
		free_parser_config(cfg_out);
		free_map_grid(map_out);
	}
	return (state->has_invalid);
}

int	load_file_lines_data(int fd, const char *source_path,
		t_parser_config *cfg_out, t_map_grid *map_out)
{
	t_line_state	state;
	char			*line;

	state.has_invalid = 0;
	state.line_no = 1;
	state.has_map_started = 0;
	init_parser_config(cfg_out);
	init_map_grid(map_out);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		process_line_content(line, cfg_out, map_out, &state);
		free(line);
		state.line_no++;
	}
	return (finalize_parsed_data(&state, cfg_out, map_out, source_path));
}
