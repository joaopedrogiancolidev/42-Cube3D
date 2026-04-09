*This project was created as part of the 42 curriculum by jgiancol, armeneze.*

<h1 align="center">Cube3D</h1>

<div align="center">
	<h3>A small raycasting engine in C with MLX42</h3>
</div>

<div align="center">
	<a href="https://github.com/joaopedrogiancolidev/42_Cube3D/stargazers">
		<img src="https://img.shields.io/github/stars/joaopedrogiancolidev/42_Cube3D?style=flat&color=purple" alt="Stars">
	</a>
	<a href="https://github.com/joaopedrogiancolidev/42_Cube3D/network/members">
		<img src="https://img.shields.io/github/forks/joaopedrogiancolidev/42_Cube3D?style=flat&color=87CEEB" alt="Forks">
	</a>
	<img src="https://img.shields.io/github/languages/top/joaopedrogiancolidev/42_Cube3D?style=flat&color=4c1" alt="Top Language">
	<img src="https://img.shields.io/github/last-commit/joaopedrogiancolidev/42_Cube3D?style=flat&color=e05d44" alt="Last Commit">
	<a href="https://www.linkedin.com/in/jpgusp/">
		<img src="https://img.shields.io/badge/LinkedIn-Jo%C3%A3o%20Pedro-blue?style=flat&logo=linkedin" alt="LinkedIn">
	</a>
</div>

---

## 📚 Table of Contents

1. [Description](#description)
2. [Instructions](#instructions)
	 - [Dependencies](#dependencies)
	 - [Compilation](#compilation)
	 - [Execution](#execution)
3. [Screenshots & GIFs](#screenshots--gifs)
4. [Technical Overview](#technical-overview)
5. [Parser Pipeline](#parser-pipeline)
6. [Initialization Flow (start_cube)](#initialization-flow-start_cube)
7. [Resources](#resources)
8. [Contact](#contact)

---

## Description

Cube3D is a 42 project whose goal is to implement, in C and using MLX42, a small first-person graphics engine based on **raycasting** (Wolfenstein 3D style). From a `.cub` configuration file, the program:

- reads and validates texture paths (NO, SO, WE, EA), floor/ceiling colors and the map;
- builds an internal representation of the world as a grid of blocks (wall/floor);
- computes the player's initial position and orientation from the spawn in the map;
- initializes the window, loads textures and renders the scene in real time;
- allows movement, camera rotation, a minimap and door interaction.

The project focuses on consolidating:

- pointer manipulation, dynamic memory and complex structs;
- robust parsing of configuration files;
- vector math for 2D raycasting → 3D projection;
- integration with a small graphics library (MLX42).

---

## Instructions

### Dependencies

On Linux, you need at least:

- a C compiler (gcc/clang);
- CMake (to build MLX42);
- GLFW + OpenGL + the usual MLX42 dependencies.

You can also check the official MLX42 documentation in [libs/MLX42](libs/MLX42).

### Compilation

At the root of the project:

```bash
make
```

The Makefile will:

- build the custom libft and printf in [libs/libft](libs/libft);
- configure and build MLX42 in [libs/MLX42/build](libs/MLX42/build);
- compile all sources in [src](src) and generate the `game` executable.

To clean objects and binaries:

```bash
make clean    # remove object files
make fclean   # also remove the binary and MLX42 build
make re       # rebuild everything from scratch
```

### Execution

After compilation:

```bash
./game sample_maps/valid_arthur.cub
```

or any other valid map in [sample_maps](sample_maps).

Typical controls (may vary slightly depending on the implementation):

- `W / A / S / D` – move the player in the 2D plane;
- `← / →` or `Q / E` – rotate the camera;
- `SPACE` – interact with doors (open/close) close to the player;
- `ESC` – close the window and exit the program.

---

## Screenshots & GIFs

Below are some example placeholders. Replace the image files with your own captures from the game.

<div align="center">

	<!-- Main in-game screenshot -->
	<img src="assets/cube3d_main.png" alt="Cube3D main view" width="600" />

	<!-- Short gameplay GIF -->
	<br/><br/>
	<img src="assets/cube3d_gameplay.gif" alt="Cube3D gameplay" width="600" />

</div>

---

## Technical Overview

- **Main entry point**: [src/main.c](src/main.c)
	- calls `parser(argc, argv, &cube_data)`;
	- if the parser succeeds, calls `start_cube(&cube_data)`;
	- finally, frees all memory with `free_all(&cube_data)`.

- **Parser and runtime setup**: directory [src/Parser](src/Parser)
	- reads the `.cub` file, validates syntax/semantics and fills `t_cube_data`;
	- converts the map into an `int **map` matrix (0 = walkable floor, 1 = wall/padding);
	- initializes the basic `t_raycast` fields (position, direction and camera plane).

- **Raycasting engine and game loop**: directory [src/cube](src/cube)
	- [start.c](src/cube/start.c) handles `start_cube`, the main loop and the raycasting hook;
	- [calculate_raycast.c](src/cube/calculate_raycast.c) and related functions implement the DDA algorithm;
	- [calculate_movement.c](src/cube/calculate_movement.c) handles movement/rotation;
	- [minimap.c](src/image/minimap.c) draws the dynamic minimap.

- **Images and MLX42**: directory [src/image](src/image)
	- wrappers around MLX images, window creation and pixel buffers.

---

## Parser Pipeline

The parser is responsible for transforming the `.cub` file into a `t_cube_data` ready for the rendering engine. The high-level flow is:

1. **Basic read and setup**
	 - `parser()` reads the `.cub` line by line into temporary internal structs (`t_parser_config`, `t_map_grid`).
	 - At the beginning, `ft_memset(cube_data, 0, sizeof(*cube_data))` ensures that all `t_cube_data` and `t_raycast` fields start as zero/NULL.

2. **NO / SO / WE / EA textures**
	 - Lines starting with `NO`, `SO`, `WE`, `EA` are parsed, normalized and validated.
	 - After `validate_texture_path()`, for a map like `valid_arthur.cub`, we get something like:
		 - `cube_data.no_path -> "src/sample_maps/./textures/north.png"`
		 - `cube_data.so_path -> "src/sample_maps/./textures/south.png"`
		 - `cube_data.we_path -> "src/sample_maps/./textures/west.png"`
		 - `cube_data.ea_path -> "src/sample_maps/./textures/east.png"`
	 - The resulting paths are guaranteed to be openable from the CWD, ready for `mlx_load_png` in `start_cube`.

3. **Floor and ceiling colors (F / C)**
	 - Lines like:
		 - `F 90,170,90`
		 - `C 255,190,140`
	 - are parsed by `parse_rgb_triplet()` and then copied to `cube_data` in `transfer_config_to_cube()`:
		 - `cube_data.floor_rgb = {90, 170, 90}`
		 - `cube_data.ceiling_rgb = {255, 190, 140}`

4. **Map grid: width, height and normalization**
	 - The map block (after the configuration block) is read into `t_map_grid`.
	 - Example summary (for `valid_arthur.cub`):
		 - `cube_data.map_height = 15`
		 - `cube_data.map_width  = 41`
	 - `extract_map_grid()` ensures that all map lines have the same length (`width`), padding with spaces to the right.

5. **Conversion to `int **map` (0/1)**
	 - `copy_runtime_map()` applies the rule cell by cell:
		 - if the character is `'1'` or `' '` → `cube_data.map[row][col] = 1` (wall/padding);
		 - otherwise (`'0'`, `'N'`, `'S'`, `'E'`, `'W'`) → `cube_data.map[row][col] = 0` (walkable floor).
	 - Interpretation:
		 - `1` = wall or outside area (padding to guarantee a closed map);
		 - `0` = walkable floor (including the original spawn cell, later separated into `t_raycast`).

6. **Player spawn and initial orientation (`t_raycast`)**
	 - The spawn character (`'N'`, `'S'`, `'E'` or `'W'`) is detected while filling map lines.
	 - Example (`'N'` found at map line `y=9`, column `x=20`, 0-based inside the map block):
		 - `cube_data.raycast.pos_x = x + 0.5 = 20.5`
		 - `cube_data.raycast.pos_y = y + 0.5 = 9.5`
	 - `set_spawn_orientation(&cube_data->raycast, 'N')` sets:
		 - `dir_x   = 0.0`
		 - `dir_y   = -1.0`
		 - `plane_x = 0.66`
		 - `plane_y` adjusted in `set_raycast_dir_plane` (for this case, `plane_y = 0.0`).
	 - At the end of the parser (before `start_cube()`), we have:
		 - `raycast.pos   = (20.5, 9.5)`
		 - `raycast.dir   = (0.0, -1.0)`
		 - `raycast.plane = (0.66, 0.0)`
		 - `raycast.old_time = 0`.
	 - All other `t_raycast` fields (raydir, delta_dist, side_dist, etc.) are still zero and will be filled during the raycasting loop.

7. **Cleaning temporary structs**
	 - In the parser happy path:
		 - `free_parser_config(&cfg)` and `free_map_grid(&map_grid)` are called;
		 - only the content actually copied into `t_cube_data` is used by the rest of the program.

In short, at this point:

```c
if (parser(argc, argv, &cube_data) != 0)
		return (1);
// here, before start_cube()
```

`cube_data` already contains:

- valid texture paths;
- properly configured `floor_rgb` and `ceiling_rgb`;
- a normalized map (`map_width`, `map_height`, binary `int **map` 0/1);
- the player's initial position and orientation in `t_raycast`;
- all graphics-related fields (MLX, images, loaded textures, window sizes) still as 0/NULL, ready to be filled in `start_cube()`.

---

## Initialization Flow (start_cube)

The `start_cube` function in [src/cube/start.c](src/cube/start.c) connects the parser to the MLX42 rendering engine.

Step by step:

1. **MLX initialization**
	 - `init_mlx(cube_data);`
	 - creates the main window (`cube_data->mlx`) and sets the render dimensions (`win_width`, `win_height`).

2. **Wall texture loading**
	 - `load_wall_textures(cube_data)` calls `mlx_load_png` for each texture path:
		 - `cube_data->no_path`, `so_path`, `we_path`, `ea_path`;
	 - fills `cube_data->tex_no`, `tex_so`, `tex_we`, `tex_ea` with valid texture pointers;
	 - on error, prints a readable message with `mlx_strerror(mlx_errno)` and aborts with `EXIT_FAILURE`.

3. **Image buffer creation**
	 - `create_image_cube(cube_data)` creates the main image where raycasting draws each frame (`image_cube`);
	 - `create_minimap(cube_data)` creates a separate image for the minimap (`minimap`).

4. **Game loop and raycasting hook**
	 - `mlx_loop_hook(cube_data->mlx, raycast, cube_data);`
		 - on each MLX loop iteration, the `raycast(void *param)` function is called;
	 - inside `raycast`:
		 - checks `ESC` with `mlx_is_key_down` to close the window;
		 - updates the background pixels (`refresh_pixel`);
		 - runs the raycasting algorithm (`calculate_raycast`);
		 - applies movement and rotation (`calculate_rotation_and_movement`);
		 - clears minimap pixels and redraws it with `draw_moving_minimap`.

5. **Door interaction**
	 - The `door(mlx_key_data_t keydata, void *param)` function is called in response to the `SPACE` key:
		 - computes the cell in front of the player (`pos + dir * 1`);
		 - if `map[next_y][next_x] == 1`, turns it into `3` (open door);
		 - if `map[next_y][next_x] == 3`, turns it back into `1` (closed door).

6. **Clean shutdown**
	 - `mlx_loop(cube_data->mlx);` keeps the program running until the window is closed;
	 - on exit, `mlx_terminate(cube_data->mlx);` releases MLX resources;
	 - `free_all(&cube_data)` in `main` frees everything else (map, textures, etc.).

---

## Resources

Some useful references related to this project:

- **Raycasting / Old-school 3D engines**
	- Article "Lode's Computer Graphics Tutorial - Raycasting":
		- https://lodev.org/cgtutor/raycasting.html
	- General explanations about Wolfenstein 3D–style engines.

- **MLX / MLX42**
	- Official MLX42 repository (included in [libs/MLX42](libs/MLX42)) and documentation in `docs/`.

- **42 & related projects**
	- Official Cube3D subject/PDF (42 intranet);
	- related projects such as so_long, FdF and miniRT.

---


## Contact

- João Pedro Giancoli – [LinkedIn](https://www.linkedin.com/in/jpgusp/)
- GitHub – https://github.com/joaopedrogiancolidev

Feel free to open *issues* or *pull requests* with suggestions, bug fixes or improvements to the architecture/organization of the code.
