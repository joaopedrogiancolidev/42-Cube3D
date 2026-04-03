/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:36:48 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/03 15:36:50 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CONFIG_H
# define PARSER_CONFIG_H

typedef struct s_parser_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*f_raw;
	char	*c_raw;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
}t_parser_config;

void	init_parser_config(t_parser_config *cfg);
void	free_parser_config(t_parser_config *cfg);

#endif