/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 09:20:17 by arthur            #+#    #+#             */
/*   Updated: 2026/03/16 09:22:06 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **open_file_array(char *path)
{
    FILE *file = fopen(path, "r");
    if (!file)
        return NULL;

    int rows = 0;
    char *line = NULL;
    size_t len = 0;

    // Count rows
    while (getline(&line, &len, file) != -1)
    {
        rows++;
    }
    free(line);
    rewind(file);

    int **map = malloc(rows * sizeof(int *));
    if (!map)
    {
        fclose(file);
        return NULL;
    }

    int row = 0;
    while (getline(&line, &len, file) != -1)
    {
        // Remove newline
        line[strcspn(line, "\n")] = 0;

        // Save line for parsing
        char *line_copy = strdup(line);
        if (!line_copy)
        {
            // Free allocated map
            for (int i = 0; i < row; i++)
                free(map[i]);
            free(map);
            free(line);
            fclose(file);
            return NULL;
        }

        // Count columns
        char *token = strtok(line_copy, " ");
        int cols = 0;
        while (token)
        {
            cols++;
            token = strtok(NULL, " ");
        }

        // Allocate row
        map[row] = malloc(cols * sizeof(int));
        if (!map[row])
        {
            free(line_copy);
            for (int i = 0; i < row; i++)
                free(map[i]);
            free(map);
            free(line);
            fclose(file);
            return NULL;
        }

        // Parse again
        free(line_copy);
        line_copy = strdup(line);
        token = strtok(line_copy, " ");
        int col = 0;
        while (token)
        {
            map[row][col++] = atoi(token);
            token = strtok(NULL, " ");
        }
        free(line_copy);
        row++;
    }
    free(line);
    fclose(file);
    return map;
}