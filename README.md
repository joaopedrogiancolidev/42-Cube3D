# Cube3D — Raycasting Engine (42 Project)

Implementação didática de um raycaster 3D usando MLX42, seguindo a estrutura e regras da escola 42.

## Parser:

O objetivo é **criar um parser robusto** para validar e carregar mapas `.cub`.


### Clonagem (com Submodules)

```bash
# Opção 1: Clone com submodule já inicializado
git clone --recurse-submodules https://github.com/joaopedrogiancolidev/42-Cube3D.git

# Opção 2: Clone normal, depois inicialize
git clone https://github.com/joaopedrogiancolidev/42-Cube3D.git
cd 42-Cube3D
git submodule update --init --recursive
```

> **Nota**: MLX42 é um git submodule — ele será clonado automaticamente com `--recurse-submodules`.

### Quick Start

```bash
cd 'Cube 3D/Parser'
make                            # Build
make debug                      # Build with debug output
make re                         # Rebuild from scratch

./parser_demo ../sample_maps/valid_minimal.cub
```

### Estrutura

```
Cube 3D/
├── Parser/                 # Protótipo de parser (semana 1)
│   ├── includes/          # Headers
│   ├── src/               # Sources (parsing)
│   ├── Makefile
│   └── obj/              # Build artifacts
├── sample_maps/           # Mapas de teste
├── MLX-42_studies/        # Estudos prévios
├── MLX42/                 # Biblioteca MLX42 (submodule)
└── Makefile              # Build raiz (placeholder)
```

### Recursos

- **MLX42**: https://github.com/codam-coding-college/MLX42
- **Raycasting Tutorial**: https://lodev.org/cgtutor/raycasting.html

## Próximos Passos

1. **Completar Parser (6 dias)** → Ver PARSER_DEV_GUIDE.md
2. **Raycasting Loop** → Integrar DDA e ray-wall collision
3. **Render com Texturas** → Carregar NO/SO/WE/EA e mapear na tela
4. **Controles** → WASD + setas para mover e rodar
5. **Otimizações e Bônus** → Minimap, sprites, etc

## Notas de Desenvolvimento

- Use `make debug` para ativar prints internos
- Use `make re` para rebuild limpo
- Compile frequentemente: `make` → teste → refatore
- Estude o arquivo `.cub` antes de parsear
- Leia o código anterior antes de escrever novo

---

