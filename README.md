# Cube3D — Raycasting Engine (42 Project)

Implementação didática de um raycaster 3D usando MLX42, seguindo a estrutura e regras da escola 42.

## Semana 1: Parser (10/03 - 15/03/2026)

O objetivo da primeira semana é **criar um parser robusto** para validar e carregar mapas `.cub`.

### Documentos Importantes

- **[RESUMO_SEMANA_1.md](RESUMO_SEMANA_1.md)** — Visão geral do que foi feito, estrutura de projeto, próximos passos.
- **[SPRINT_6_DAYS_PARSER.md](SPRINT_6_DAYS_PARSER.md)** — Guia detalhado dia a dia com cronograma, testes e debug.

### Quick Start

```bash
cd 'Cube 3D/Parser'
make                           # Build
make debug                      # Build with debug output
make visual                     # Build with MLX viewer

./parser_demo ../sample_maps/valid_minimal.cub
./visual_demo ../sample_maps/valid_minimal.cub
```

### Estrutura

```
Cube 3D/
├── Parser/                 # Protótipo de parser (semana 1)
│   ├── includes/          # Headers
│   ├── src/               # Sources (parsing, utils, visual)
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

1. **Completar Parser (6 dias)** → Ver SPRINT_6_DAYS_PARSER.md
2. **Raycasting Loop** → Integrar DDA e ray-wall collision
3. **Render com Texturas** → Carregar NO/SO/WE/EA e mapear na tela
4. **Controles** → WASD + setas para mover e rodar
5. **Otimizações e Bônus** → Minimap, sprites, etc

## Notas de Desenvolvimento

- Use `make debug` para ativar prints internos
- Use `make visual` para abrir visualizador 2D do mapa
- Compile frequentemente: `make` → teste → refatore
- Estude o arquivo `.cub` antes de parsear
- Leia o código anterior antes de escrever novo

---

*Sprint iniciado: 10/03/2026*
