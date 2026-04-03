/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:36:58 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/03 15:37:00 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ERRORS_H
# define PARSER_ERRORS_H

void	parser_error_invalid_line(int line_no);
void	parser_error_element_after_map(int line_no);
void	parser_error_duplicate(const char *key, int line_no);
void	parser_error_missing(const char *key);
void	parser_error_malloc(const char *key, int line_no);
void	parser_error_map_invalid_char(int row, int col, char c);
void	parser_error_spawn_count(int spawn_count);
void	parser_error_map_open(int row, int col, char c);
void	parser_error_invalid_rgb(const char *key);
void	parser_error_invalid_texture(const char *key, const char *path);
void	parser_error_usage(void);
void	parser_error_file_open(const char *path);
void	parser_error_invalid_extension(const char *path);

#endif