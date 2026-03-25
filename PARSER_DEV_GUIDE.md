# Parser Development Guide - Updated

Last Updated: 2026-03-25
Branch: parser

---

## Scope Status (Days 1-6)

### Day 1 ✅ Stable file reading and line typing
- get_next_line orchestration is stable.
- Line classification works with EMPTY, ELEMENT, MAP, INVALID.

### Day 2 ✅ Element parsing and validation
- Free order of NO/SO/WE/EA/F/C is supported.
- Duplicate and missing checks are active.
- Texture path validation is active for NO/SO/WE/EA.
- Texture paths are resolved with fallback relative to the source .cub directory.
- RGB validation is active for F/C with strict R,G,B in [0,255].

### Day 3 ✅ Map extraction and normalization
- Raw map block is accumulated line by line.
- Map is normalized to rectangular grid with space padding.

### Day 4 ✅ Structural map validation
- Allowed map charset is enforced.
- Exactly 1 spawn (N/S/E/W) is enforced.

### Day 5 ✅ Map closure validation
- Any walkable cell (0 or spawn) touching map boundary or void is rejected.

### Day 6 ✅ Delivery consolidation
- Pipeline is centralized in parse_cub_file(path).
- main_parser.c is CLI-only and delegates parser work.
- Input path must use .cub extension.
- Error output follows subject-style contract: Error then explicit message.

---

## Essential Commands

```bash
cd "/home/jgiancol/42_Projects/M4/Cube3D/Cube 3D/Parser"
make -s re
```

Quick smoke:

```bash
./parser_demo ../sample_maps/valid_minimal.cub ; echo "EXIT:$?"
```

---

## Manual Validation Suite

### Core maps

```bash
for f in \
  ../sample_maps/valid_minimal.cub \
  ../sample_maps/invalid_char.cub \
  ../sample_maps/two_spawns_invalid.cub \
  ../sample_maps/invalid_open.cub; do
  echo "--- $f ---"
  ./parser_demo "$f"
  echo "EXIT:$?"
  echo
done
```

### Usage and open-fail

```bash
./parser_demo ; echo "EXIT:$?"
./parser_demo ../sample_maps/valid_minimal.txt ; echo "EXIT:$?"
./parser_demo ../sample_maps/does_not_exist.cub ; echo "EXIT:$?"
```

### Relative texture-path sample

```bash
test_root='/tmp/cub_rel_test'
rm -rf "$test_root"
mkdir -p "$test_root/assets"
echo north > "$test_root/assets/north.png"
echo south > "$test_root/assets/south.png"
echo west > "$test_root/assets/west.png"
echo east > "$test_root/assets/east.png"
cat > "$test_root/scene.cub" << 'EOF'
NO ./assets/north.png
SO ./assets/south.png
WE ./assets/west.png
EA ./assets/east.png
F 220,100,0
C 225,30,0

1111
1N01
1111
EOF
./parser_demo "$test_root/scene.cub" ; echo "EXIT:$?"
```

### RGB invalid sample

```bash
tmp='/tmp/cub_invalid_rgb.cub'
printf '%s\n' \
'NO ./textures/north.png' \
'SO ./textures/south.png' \
'WE ./textures/west.png' \
'EA ./textures/east.png' \
'F 300,100,0' \
'C 225,30,0' \
'' \
'1111' \
'1N01' \
'1111' > "$tmp"
./parser_demo "$tmp" ; echo "EXIT:$?"
```

### Texture invalid sample

```bash
tmp='/tmp/cub_invalid_texture.cub'
printf '%s\n' \
'NO ./textures/does_not_exist.png' \
'SO ./textures/south.png' \
'WE ./textures/west.png' \
'EA ./textures/east.png' \
'F 220,100,0' \
'C 225,30,0' \
'' \
'1111' \
'1N01' \
'1111' > "$tmp"
./parser_demo "$tmp" ; echo "EXIT:$?"
```

---

## Expected Results (Current)

| Case | Expected |
|------|----------|
| valid_minimal.cub | EXIT:0 |
| invalid_char.cub | EXIT:1 + invalid map character message |
| two_spawns_invalid.cub | EXIT:1 + spawn count message |
| invalid_open.cub | EXIT:1 + open map message |
| invalid RGB sample | EXIT:1 + invalid RGB message |
| invalid texture sample | EXIT:1 + invalid texture path message |
| usage without args | EXIT:1 + usage message |
| wrong file extension | EXIT:1 + invalid extension message |
| missing file path | EXIT:1 + open-file message |
| relative texture sample | EXIT:0 |

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
├── src/
│   ├── main_parser.c
│   └── parsing/
│       ├── reader/read_lines.c
│       ├── reader/parse_cub_file.c
│       ├── types/line_types.c
│       ├── config/parser_config.c
│       ├── elements/elements_parse.c
│       ├── elements/elements_validate.c
│       ├── map/map_grid_utils.c
│       ├── map/map_extract.c
│       ├── map/map_validate.c
│       └── utils/parser_errors.c
└── textures/
    ├── north.png
    ├── south.png
    ├── west.png
    └── east.png
```

---

## Execution Flow

```text
main_parser.c
  -> parse_cub_file(path)
      -> load_file_lines(fd)
          -> line_type_name()
          -> parse_element_line()
          -> add_map_line()
      -> validate_required_elements()
          -> validate_texture_path()
          -> validate_rgb_value()
      -> extract_map_grid()
      -> validate_map_charset_and_spawn()
      -> validate_map_closed()
      -> free_parser_config()
      -> free_map_grid()
```

---

## Debug Notes

With make -s debug, parser prints phase-focused logs:

- [DEBUG] line classifier checks
- [LINE N] type and raw content
- [MAP GRID] width and height
- [MAP i] normalized map rows
- [MAP VALIDATE] spawn count and open-map diagnostics

---

## Team Standard

1. One module per responsibility.
2. parser.h remains aggregate include for parser internals.
3. Keep validation order: elements -> map normalize -> structure -> closure.
4. Keep explicit and contextual error messages.
5. Keep release output minimal and debug output actionable.

---

## Integration Handoff

Use PARSER_INTEGRATION_GUIDE.md as the official teammate-facing contract for:

1. parser entrypoint usage
2. structs and field semantics
3. return/error behavior
4. module boundaries and responsibilities
