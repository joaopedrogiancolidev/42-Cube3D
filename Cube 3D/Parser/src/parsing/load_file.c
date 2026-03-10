#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG_PARSER
# define DBG(fmt, ...) fprintf(stderr, "[DEBUG] " fmt "\n", ##__VA_ARGS__)
#else
# define DBG(fmt, ...) (void)0
#endif

static char	*dup_line_without_newline(const char *line)
{
	size_t	len;
	char	*copy;

	len = strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	memcpy(copy, line, len);
	copy[len] = '\0';
	return (copy);
}

static int	grow_lines_buffer(t_file_lines *file_lines, size_t *capacity)
{
	char	**new_lines;
	size_t	new_capacity;

	new_capacity = (*capacity) * 2;
	DBG("grow buffer: %zu -> %zu", *capacity, new_capacity);
	new_lines = realloc(file_lines->lines, sizeof(char *) * new_capacity);
	if (!new_lines)
		return (0);
	file_lines->lines = new_lines;
	*capacity = new_capacity;
	return (1);
}

int	load_file_lines(const char *path, t_file_lines *file_lines)
{
	FILE	*fp;
	char	*line;
	size_t	len;
	ssize_t	read_bytes;
	size_t	capacity;

	fp = fopen(path, "r");
	if (!fp)
	{
		DBG("failed to open file: %s", path);
		return (0);
	}
	DBG("opened file: %s", path);
	file_lines->count = 0;
	capacity = 8;
	file_lines->lines = malloc(sizeof(char *) * capacity);
	if (!file_lines->lines)
	{
		DBG("malloc failed for lines buffer");
		return (fclose(fp), 0);
	}
	line = NULL;
	len = 0;
	read_bytes = getline(&line, &len, fp);
	while (read_bytes != -1)
	{
		if (file_lines->count == capacity && !grow_lines_buffer(file_lines, &capacity))
		{
			DBG("realloc failed while growing lines buffer");
			return (free(line), fclose(fp), 0);
		}
		DBG("read line[%zu] (%zd bytes)", file_lines->count, read_bytes);
		file_lines->lines[file_lines->count] = dup_line_without_newline(line);
		if (!file_lines->lines[file_lines->count])
		{
			DBG("malloc failed duplicating line[%zu]", file_lines->count);
			return (free(line), fclose(fp), 0);
		}
		file_lines->count++;
		read_bytes = getline(&line, &len, fp);
	}
	free(line);
	fclose(fp);
	DBG("finished reading file: total lines = %zu", file_lines->count);
	return (1);
}