# Parser Development Guide - Updated

**Last Updated:** 2026-03-25  
**Branch:** `parser`

---

## Scope Status (Days 1-4)

### Day 1 ✅ Stable file reading and line typing
- `get_next_line` orchestration is stable.
- Line classification works with: `EMPTY`, `ELEMENT`, `MAP`, `INVALID`.
- Implemented in `line_types.c` and consumed by `load_file_lines`.

### Day 2 ✅ Element parsing (`NO/SO/WE/EA/F/C`)
- Free order is supported.
- Duplicate and missing checks are active.
- Errors are explicit:
  - `duplicate element 'X' at line N`
  - `missing required element 'X'`
  - `element after map started at line N`

### Day 3 ✅ Map extraction and normalization
- Raw map block is accumulated line by line.
- Map is normalized to rectangular grid (space padded).
- Width is computed via `get_max_map_width`.
- Debug logs show normalized grid:
  - `[MAP GRID] width=... height=...`
  - `[MAP i] |...|`

### Day 4 ✅ Structural map validation
- Valid map charset is enforced.
- Exactly 1 spawn (`N/S/E/W`) is enforced.
- Specific errors are active:
  - `invalid map character 'X' at row R col C`
  - `expected exactly 1 spawn, found N`

---

## Essential Commands

Use your local path on each machine:

```bash
cd "/home/jgiancol/42_Projects/M4/Cube3D/Cube 3D/Parser"
# or
cd "/home/deck/Desktop/Github_Projetcs/42/Cube3D/Cube 3D/Parser"
```

Build normal:

```bash
make -s re
```

Build debug:

```bash
make -s debug
```

Quick smoke test:

```bash
./parser_demo ../sample_maps/valid_minimal.cub ; echo "EXIT:$?"
```

---

## Mini Guide (Manual Run + Validation)

### 1) Run one case

```bash
./parser_demo ../sample_maps/invalid_char.cub ; echo "EXIT:$?"
```

### 2) Run full suite

```bash
for f in \
  ../sample_maps/valid_minimal.cub \
  ../sample_maps/spawn_colors_demo.cub \
  ../sample_maps/ragged_valid.cub \
  ../sample_maps/leading_spaces_valid.cub \
  ../sample_maps/mixed_width_valid.cub \
  ../sample_maps/invalid_duplicate_element.cub \
  ../sample_maps/invalid_missing_element.cub \
  ../sample_maps/invalid_element_after_map.cub \
  ../sample_maps/invalid_char.cub \
  ../sample_maps/tab_in_map_invalid.cub \
  ../sample_maps/two_spawns_invalid.cub \
  ../sample_maps/invalid_open.cub; do
  echo "--- $f ---"
  ./parser_demo "$f"
  echo "EXIT:$?"
  echo
done
```

### 3) Extract only errors from output

```bash
./parser_demo ../sample_maps/invalid_char.cub 2>&1 | grep "Error:"
```

### 4) Inspect current code changes

```bash
git status -sb
git diff
```

---

## Quick Checklist (10 min)

1. `make -s debug`
2. Valid case: `valid_minimal.cub` -> `EXIT:0`
3. Day 2 invalids:
   - `invalid_duplicate_element.cub` -> `EXIT:1`
   - `invalid_missing_element.cub` -> `EXIT:1`
   - `invalid_element_after_map.cub` -> `EXIT:1`
4. Day 3 map-shape checks:
   - `ragged_valid.cub` -> `EXIT:0`
   - `leading_spaces_valid.cub` -> `EXIT:0`
   - `mixed_width_valid.cub` -> `EXIT:0`
   - `tab_in_map_invalid.cub` -> `EXIT:1`
5. Day 4 structure checks:
   - `invalid_char.cub` -> `EXIT:1` + invalid char message
   - `two_spawns_invalid.cub` -> `EXIT:1` + spawn count message
6. Keep in mind: `invalid_open.cub` is still `EXIT:0` until Day 5.

---

## Expected Results (Current)

| Map | Expected |
|-----|----------|
| `valid_minimal.cub` | `EXIT:0` |
| `ragged_valid.cub` | `EXIT:0` |
| `leading_spaces_valid.cub` | `EXIT:0` |
| `mixed_width_valid.cub` | `EXIT:0` |
| `invalid_duplicate_element.cub` | `EXIT:1` |
| `invalid_missing_element.cub` | `EXIT:1` |
| `invalid_element_after_map.cub` | `EXIT:1` |
| `invalid_char.cub` | `EXIT:1` (invalid map character) |
| `tab_in_map_invalid.cub` | `EXIT:1` |
| `two_spawns_invalid.cub` | `EXIT:1` (spawn count != 1) |
| `spawn_colors_demo.cub` | `EXIT:1` (contains multiple spawns by design) |
| `invalid_open.cub` | `EXIT:0` (closure not implemented yet) |

---

## Parser Structure

```text
Cube 3D/Parser/
├── includes/
│   ├── parser.h
│   ├── parsing.h
│   ├── parser_config.h
│   ├── elements.h
│   ├── map_grid.h
│   ├── map_validate.h
│   ├── parser_errors.h
│   └── debug.h
└── src/
    ├── main_parser.c
    └── parsing/
        ├── reader/read_lines.c
        ├── types/line_types.c
        ├── config/parser_config.c
        ├── elements/elements_parse.c
        ├── elements/elements_validate.c
        ├── map/map_grid_utils.c
        ├── map/map_extract.c
        ├── map/map_validate.c
        └── utils/parser_errors.c
```

### Current Execution Flow

```text
main_parser.c
  -> load_file_lines(fd)
      -> line_type_name()
      -> parse_element_line()
      -> add_map_line()
      -> validate_required_elements()
      -> extract_map_grid()
      -> validate_map_charset_and_spawn()
      -> free_parser_config()
      -> free_map_grid()
```

---

## Implementation Plan Status

### Day 1 - stable read base ✅
- `load_file_lines`, `is_empty_line`, `is_map_line`, `is_element_line`.

### Day 2 - elements ✅
- Parse `NO/SO/WE/EA/F/C`, duplicates, missing, and order handling.

### Day 3 - map extraction/normalization ✅
- Rectangular grid extraction with padding.

### Day 4 - structural map validation ✅
- Charset validation and exactly 1 spawn.

### Day 5 - map closure validation
- Validate closed map (no walkable/spawn touching void or boundaries).

### Day 6 - delivery consolidation
- Final pipeline cleanup and standardized error/return integration.

---

## Debug Notes (Day 2-4)

With `make -s debug`, parser prints:
- `[DEBUG] is_*` line checks
- `[LINE N] TYPE | content`
- `[MAP GRID] width=... height=...`
- `[MAP i] |...|`
- `[MAP VALIDATE] spawn_count=N`

---

## Code Organization Standard (Team Pattern)

This pattern is now applied across Days 1-4 and should remain the default:

1. One module per responsibility.
   - `types/` only classifies lines.
   - `elements/` only parses/validates elements.
   - `map/` handles accumulation, normalization, and map-specific validation.
   - `utils/` centralizes parser errors.

2. Header-first integration.
   - Public function contracts stay in `includes/*.h`.
   - `parser.h` aggregates module headers for parser internals.

3. Function comments must explain:
   - why the function exists,
   - where it is called,
   - what phase of pipeline it belongs to.

4. Debug macros are explicit and phase-oriented.
   - Keep release output clean.
   - Keep debug output actionable for each stage.

5. Validation order must follow data readiness.
   - Parse elements -> extract map -> normalize -> validate structure -> (Day 5 closure).

6. Error messages should be specific and local.
   - Report exact context whenever possible (line/row/col).

---

## Next Focus

Start Day 5 using the same modular pattern:
1. Add dedicated map-closure module.
2. Add closure-specific error functions.
3. Add closure-focused sample maps and test loop.
