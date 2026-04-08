/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 21:10:00 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/07 21:49:12 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_rgb_component(const char **p, int *out)
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

int	parse_rgb_triplet(char *raw, int rgb[3])
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

int	validate_rgb_value(char *raw, const char *key, int rgb[3])
{
	if (parse_rgb_triplet(raw, rgb) != 0)
	{
		parser_error_invalid_rgb(key);
		return (1);
	}
	return (0);
}
