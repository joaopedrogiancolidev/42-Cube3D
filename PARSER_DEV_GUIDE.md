# Parser Development Guide - Quick Reference

**Last Updated:** 2026-03-18  
**Current Branch:** `parser`  
**Last Commit:** `19e284b` - "refactor: clean up parser debug macros and add visual separator"

---

## ⚡ Quick Start (Copy-Paste)

```bash
cd "/home/deck/Desktop/Github_Projetcs/42/Cube3D/Cube 3D/Parser"

# Clean build + test (normal mode - shows only errors)
make -s re && ./parser_demo ../sample_maps/invalid_char.cub ; echo "EXIT:$?"

# Clean build + test (debug mode - shows detailed logs)
make -s debug && ./parser_demo ../sample_maps/invalid_char.cub ; echo "EXIT:$?"

# Test all maps
for f in ../sample_maps/*.cub; do echo "=== $f ==="; ./parser_demo "$f"; echo "EXIT:$?"; echo; done
```

---

## 📊 Current State

### What Works ✅
- **File reading:** `get_next_line` reads `.cub` files line-by-line
- **Line classification:** 4 types (EMPTY, ELEMENT, MAP, INVALID)
- **Error detection:** Invalid chars (like `X`) are caught
- **Two build modes:** `make re` (clean), `make debug` (verbose)

### Classification Rules (Hard-coded)
```
EMPTY     → Only whitespace or empty
ELEMENT   → Starts with NO, SO, WE, EA, F, C
MAP       → Contains 0, 1, N, S, E, W, or spaces
INVALID   → Anything else
```

### Exit Codes
- `0` = All lines parsed OK
- `1` = At least one INVALID line found

### Test Maps
| Map | Status | Expected |
|-----|--------|----------|
| `valid_minimal.cub` | ✅ WORKS | EXIT:0, no error |
| `invalid_char.cub` | ✅ WORKS | EXIT:1, "invalid line at 10" |
| `invalid_open.cub` | ✅ WORKS | EXIT:0 (boundary check not yet) |
| `spawn_colors_demo.cub` | ✅ WORKS | EXIT:0 (spawn points supported) |

---

## 🛠️ Build & Test Commands

### Mode: Normal (Production-like)
```bash
make re                    # Full rebuild
./parser_demo ../sample_maps/valid_minimal.cub
echo $?                    # Shows EXIT code
```
**Output:** Only errors (clean terminal)

### Mode: Debug (Development)
```bash
make debug                 # Full rebuild with -DDEBUG_PARSER
./parser_demo ../sample_maps/valid_minimal.cub
echo $?
```
**Output:** [DEBUG] traces + [LINE N] details + errors

### One-Liner with Visual Separator
```bash
make -s re && ./parser_demo ../sample_maps/invalid_char.cub ; echo "EXIT:$?"
```

### Silent Mode (Hide build output)
```bash
make -s re    # Same as make re but quieter
make -s debug # Same as make debug but quieter
```

---

## 📁 File Structure (Parser)

```
Cube 3D/Parser/
├── Makefile                      # Targets: make, make debug, make re
├── includes/
│   ├── debug.h                   # Macros: DBG_LINE, DBG_CLASSIFIED_LINE
│   ├── parser.h                  # Main include (includes debug.h + parsing.h)
│   └── parsing.h                 # Function prototypes
├── src/
│   ├── main_parser.c             # main() + print_visual_separator()
│   └── parsing/
│       ├── line_types.c          # is_empty_line, is_element_line, is_map_line, line_type_name
│       └── read_lines.c          # classify_file_lines (entry point)
└── sample_maps/
    ├── valid_minimal.cub         # 5x5 simple map
    ├── invalid_char.cub          # Line 10 has 'X' (invalid)
    ├── invalid_open.cub          # Not fully enclosed (check later)
    └── spawn_colors_demo.cub     # With spawn points N/S/E/W
```

---

## 🔍 Debug Macros (In debug.h)

**When `make re` (normal):**
```c
#define DBG_LINE(...) ((void)0)              // → Does nothing
#define DBG_CLASSIFIED_LINE(...) ((void)0)   // → Does nothing
```

**When `make debug`:**
```c
#define DBG_LINE(fn, result) ft_printf("[DEBUG] %s -> %d\n", fn, result)
#define DBG_CLASSIFIED_LINE(line_no, line_type, line) \
        ft_printf("[LINE %d] %s | %s", line_no, line_type, line)
```

**Example output (debug mode):**
```
[DEBUG] is_empty_line -> 0
[DEBUG] is_element_line -> 1
[LINE 1] ELEMENT | NO ./textures/north.png
...
Error: invalid line at 10
[LINE 10] INVALID | 10N0X1
EXIT:1
```

---

## 🎯 Next Steps (Priority Order)

### Phase 1: Parser State Machine (Next Session)
- [ ] Implement CONFIG state: expect elements (NO/SO/WE/EA/F/C)
- [ ] Implement MAP state: expect map lines (0/1/N/S/E/W)
- [ ] **Validation:** Each element appears **exactly once** in CONFIG
- [ ] **Boundary:** Clear transition from CONFIG→MAP (no interleaving)
- [ ] **Error handling:** Report which element is duplicate/missing/out-of-order

**Files to modify:**
- `parsing.h` → Add new function prototypes
- `line_types.c` → Add element type checking (NO vs SO vs etc)
- `read_lines.c` → Rewrite as state machine instead of just classification

### Phase 2: RGB Parsing
- [ ] Parse `F 220,100,0` → Extract R, G, B
- [ ] Validate each component in range [0, 255]
- [ ] Store in struct for later use

### Phase 3: Map Validation
- [ ] Check that map is fully enclosed by `1` (walls)
- [ ] Validate spawn point (`N/S/E/W`) appears exactly once

### Phase 4: Integration
- [ ] Return structured data (not just EXIT code)
- [ ] Memory: Free all allocated resources
- [ ] Connect to MLX42 for visual rendering

---

## 🐛 Known Issues & Tech Debt

| Issue | Severity | Note |
|-------|----------|------|
| `.vscode/` in git | Low | Remove before submission |
| `obj/` & `parser_demo` in git | Low | Add to `.gitignore` |
| Debug output has trailing `\n` | Low | By design (from `get_next_line`), acceptable |
| No enum for line types | Medium | Currently uses `char *` strings; refactor later |
| No memory validation | Medium | Check for leaks before final commit |

---

## 🧠 Key Decisions Made This Session

1. **Debug Macros Consolidated** → All in `debug.h` (clean code)
2. **Removed inline #ifdef from functions** → Calls `DBG_*` macros instead
3. **Visual separator added** → Makes terminal output easier to read
4. **Line classification logic in `line_types.c`** → Easier to extend for state machine

---

## ❓ Common Debugging Tips

**Q: Build doesn't seem to work?**
```bash
make fclean  # Remove everything
make re      # Rebuild from scratch
```

**Q: Debug output looks wrong?**
```bash
make debug   # Ensure you're actually in debug mode
# vs
make re      # vs normal mode
```

**Q: How do I add a new .cub test file?**
```bash
# Create file in ../sample_maps/my_test.cub
# Then run:
./parser_demo ../sample_maps/my_test.cub ; echo "EXIT:$?"
```

**Q: Parser crashes on valid input?**
```bash
# Run in debug to see where it fails:
make debug && ./parser_demo ../sample_maps/valid_minimal.cub
```

---

## 📝 How to Use This File Tomorrow

1. **Read "Quick Start" section** → Copy-paste commands
2. **Check "Current State" section** → Understand what already works
3. **Review "Next Steps"** → Pick the next task
4. **Reference "File Structure"** → Know where to edit
5. **Use "Debug Macros" section** → Understand compilation behavior

---

**Meta Note for AI:** This file should be updated after each session with new learnings, issues, or changes to the development flow.
