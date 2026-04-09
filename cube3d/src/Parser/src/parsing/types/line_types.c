/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:04:39 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/07 18:05:32 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_empty_line(char *line)
{
	int	i;
	int	result;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	result = (line[i] == '\0' || line[i] == '\n');
	return (result);
}

int	is_element_line(char *line)
{
	char	*raw_line;
	int		result;

	raw_line = line;
	(void)raw_line;
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		result = 1;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		result = 1;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		result = 1;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		result = 1;
	else if (ft_strncmp(line, "F ", 2) == 0)
		result = 1;
	else if (ft_strncmp(line, "C ", 2) == 0)
		result = 1;
	else
		result = 0;
	return (result);
}

int	is_map_line(char *line)
{
	int	i;
	int	has_map_char;
	int	result;

	i = 0;
	has_map_char = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == ' ')
		{
			i++;
			continue ;
		}
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			has_map_char = 1;
			i++;
			continue ;
		}
		result = 0;
		return (result);
	}
	result = has_map_char;
	return (result);
}

char	*line_type_name(char *line)
{
	if (is_empty_line(line))
		return ("EMPTY");
	if (is_element_line(line))
		return ("ELEMENT");
	if (is_map_line(line))
		return ("MAP");
	return ("INVALID");
}
