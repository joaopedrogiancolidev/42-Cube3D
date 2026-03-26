# Parser Integration Guide

Last Updated: 2026-03-25
Scope: Cube 3D/Parser module integration contract for teammate usage.

## Objective

This document defines how to consume the parser safely from the main Cube3D runtime, what data is produced, what validation is guaranteed, and what each parser function is responsible for.

## Single Entry Point

Primary API:

- parse_cub_file(const char *path) in Cube 3D/Parser/src/parsing/reader/parse_cub_file.c

Behavior:

1. Validates that the input path ends with .cub.
2. Opens the .cub file.
3. Delegates full parsing pipeline to load_file_lines(fd).
4. Closes the file descriptor.
5. Returns 0 on success and 1 on parse/config/map failure.

CLI wrapper:

- main(int argc, char **argv) in Cube 3D/Parser/src/main_parser.c
- This is demo-only shell behavior and should stay thin.

## Return and Error Contract

Return contract:

1. Success: function returns 0.
2. Failure: function returns 1.

Output contract for failures:

1. First line is always exactly Error
2. Second line is an explicit message describing the failure context.

Examples of explicit messages:

1. invalid line at line N
2. duplicate element 'NO' at line N
3. missing required element 'C'
4. invalid texture path for 'EA': ./path
5. invalid file extension (expected .cub): ./scene.txt
6. invalid RGB value for 'F' (expected R,G,B in [0,255])
7. invalid map character 'X' at row R col C
8. expected exactly 1 spawn, found N
9. map is open at row R col C around '0'

## Core Data Structures

Parser config container:

- t_parser_config in Cube 3D/Parser/includes/parser_config.h

Fields:

1. no_path, so_path, we_path, ea_path: texture paths as parsed strings.
2. f_raw, c_raw: raw floor/ceiling strings before conversion.
3. floor_rgb[3], ceiling_rgb[3]: validated RGB values in [0,255].

Map container:

- t_map_grid in Cube 3D/Parser/includes/map_grid.h

Fields:

1. lines: normalized rectangular grid.
2. height: number of rows.
3. width: normalized row width.

## End-to-End Pipeline

The pipeline runs in load_file_lines(fd) in Cube 3D/Parser/src/parsing/reader/read_lines.c.

1. Initialize parser structures with init_parser_config and init_map_grid.
2. Read file line-by-line with get_next_line.
3. Classify each line with line_type_name as EMPTY, ELEMENT, MAP, or INVALID.
4. Parse elements with parse_element_line.
5. Accumulate map rows with add_map_line.
6. Validate required elements with validate_required_elements.
7. Normalize map with extract_map_grid.
8. Validate map charset and spawn with validate_map_charset_and_spawn.
9. Validate closed map with validate_map_closed.
10. Free all parser-owned memory before returning.

## Module Responsibilities

Line typing:

- is_empty_line, is_element_line, is_map_line, line_type_name
- File: Cube 3D/Parser/src/parsing/types/line_types.c
- Responsibility: lexical classification only.

Reader/orchestration:

- load_file_lines and local helpers for invalid-line diagnostics.
- File: Cube 3D/Parser/src/parsing/reader/read_lines.c
- Responsibility: sequence and dispatch, not business validation details.

Elements parse:

- parse_element_line and local helpers skip_spaces, set_element_value.
- File: Cube 3D/Parser/src/parsing/elements/elements_parse.c
- Responsibility: identify NO/SO/WE/EA/F/C and store values with duplicate protection.

Elements validate:

- validate_required_elements and local RGB/texture validators.
- File: Cube 3D/Parser/src/parsing/elements/elements_validate.c
- Responsibility: mandatory checks for presence, readable texture paths, and RGB correctness.
- Texture path behavior: first tries the path as provided, then retries relative to the source .cub directory.

Map accumulation:

- init_map_grid, add_map_line, free_map_grid.
- File: Cube 3D/Parser/src/parsing/map/map_grid_utils.c
- Responsibility: dynamic map row storage.

Map normalization:

- get_max_map_width, extract_map_grid.
- File: Cube 3D/Parser/src/parsing/map/map_extract.c
- Responsibility: convert ragged rows into rectangular grid with space padding.

Map validation:

- validate_map_charset_and_spawn, validate_map_closed.
- File: Cube 3D/Parser/src/parsing/map/map_validate.c
- Responsibility: structural and closure validation on normalized grid.

Error handling:

- parser_error_* family.
- File: Cube 3D/Parser/src/parsing/utils/parser_errors.c
- Responsibility: centralized, consistent Error + explicit message output.

## Integration Notes For Teammate

1. Treat parse_cub_file as the only parser entry point.
2. Do not bypass the pipeline by calling module internals directly.
3. Keep map validation order unchanged because it matches data readiness.
4. Keep parser.h as aggregate include for parser internals.
5. If adding bonus symbols, gate them behind explicit bonus-mode decisions and avoid breaking mandatory map rules.
6. Preserve .cub extension enforcement in any higher-level wrapper.

## Manual Acceptance Smoke

From Cube 3D/Parser directory:

1. make -s re
2. ./parser_demo ../sample_maps/valid_minimal.cub ; echo "EXIT:$?"
3. ./parser_demo ../sample_maps/invalid_char.cub ; echo "EXIT:$?"
4. ./parser_demo ../sample_maps/two_spawns_invalid.cub ; echo "EXIT:$?"
5. ./parser_demo ../sample_maps/invalid_open.cub ; echo "EXIT:$?"

Expected:

1. valid_minimal returns EXIT:0
2. invalid_char returns EXIT:1 and explicit invalid character message
3. two_spawns_invalid returns EXIT:1 and explicit spawn count message
4. invalid_open returns EXIT:1 and explicit open-map message
