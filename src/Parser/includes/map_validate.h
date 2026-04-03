/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:36:16 by jgiancol          #+#    #+#             */
/*   Updated: 2026/04/03 15:36:17 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_VALIDATE_H
# define MAP_VALIDATE_H

# include "map_grid.h"

/*
** Used by load_file_lines() after extract_map_grid() to validate
** the normalized map before later gameplay-specific checks.
*/
int	validate_map_charset_and_spawn(t_map_grid *map);

/*
** Day 5: map closure validation on the normalized rectangular grid.
** Used after charset/spawn validation to ensure no walkable cell leaks to void.
*/
int	validate_map_closed(t_map_grid *map);

#endif