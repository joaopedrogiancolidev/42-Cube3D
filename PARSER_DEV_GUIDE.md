# Parser Development Guide — Atualizado

**Last Updated:** 2026-03-19  
**Branch:** `parser`

---

## 🎯 Escopo Atual (o que já está pronto)

### Dia 1 ✅ Base de leitura estável
- Leitura linha a linha funcionando via `get_next_line`.
- Classificação inicial funcionando: `EMPTY`, `ELEMENT`, `MAP`, `INVALID`.
- Funções entregues: `load_file_lines`, `is_empty_line`, `is_map_line`, `is_element_line`.
- Critério validado: debug imprime tipo detectado por linha.

### Dia 2 ✅ Parse de elementos
- Parse de `NO/SO/WE/EA/F/C` com ordem livre.
- Estrutura de config ativa e validações de duplicado/faltando.
- Erros claros implementados:
  - `duplicate element 'X' at line N`
  - `missing required element 'X'`
  - `element after map started at line N`

### Dia 3 ✅ Extração e normalização do mapa
- Bloco de mapa separado durante o parse.
- Grade retangular montada com preenchimento por espaço.
- Largura máxima calculada por `get_max_map_width`.
- Debug de normalização ativo em build debug:
  - `[MAP GRID] width=... height=...`
  - `[MAP i] |...|`

---

## ⚡ Comandos Essenciais (Terminal)

```bash
cd "/home/deck/Desktop/Github_Projetcs/42/Cube3D/Cube 3D/Parser"

# Build normal (sem debug de linha)
make -s re

# Build debug (com [DEBUG] e [LINE N])
make -s debug

# Smoke test rápido
./parser_demo ../sample_maps/valid_minimal.cub ; echo "EXIT:$?"
```

### Bateria completa (recomendada)

```bash
make -s debug && \
for f in \
  ../sample_maps/valid_minimal.cub \
  ../sample_maps/invalid_char.cub \
  ../sample_maps/invalid_open.cub \
  ../sample_maps/spawn_colors_demo.cub \
  ../sample_maps/invalid_duplicate_element.cub \
  ../sample_maps/invalid_missing_element.cub \
  ../sample_maps/invalid_element_after_map.cub \
  ../sample_maps/ragged_valid.cub \
  ../sample_maps/leading_spaces_valid.cub \
  ../sample_maps/mixed_width_valid.cub \
  ../sample_maps/tab_in_map_invalid.cub; do
  echo "--- $f ---"
  ./parser_demo "$f"
  echo "EXIT:$?"
  echo
done
```

### Testes focados do Dia 2

```bash
./parser_demo ../sample_maps/invalid_duplicate_element.cub ; echo "EXIT:$?"
./parser_demo ../sample_maps/invalid_missing_element.cub ; echo "EXIT:$?"
./parser_demo ../sample_maps/invalid_element_after_map.cub ; echo "EXIT:$?"
```

### Testes focados do Dia 3 (normalização do mapa)

```bash
./parser_demo ../sample_maps/ragged_valid.cub ; echo "EXIT:$?"
./parser_demo ../sample_maps/leading_spaces_valid.cub ; echo "EXIT:$?"
./parser_demo ../sample_maps/mixed_width_valid.cub ; echo "EXIT:$?"
./parser_demo ../sample_maps/tab_in_map_invalid.cub ; echo "EXIT:$?"
```

Esperado:
- `ragged_valid.cub` -> `EXIT:0`
- `leading_spaces_valid.cub` -> `EXIT:0`
- `mixed_width_valid.cub` -> `EXIT:0`
- `tab_in_map_invalid.cub` -> `EXIT:1` (linha inválida no mapa)

Com `make -s debug`, além do log por linha, o parser também imprime:
- `[MAP GRID] width=... height=...`
- `[MAP i] |...|`

Isso permite validar visualmente se a normalização preservou o layout do arquivo.

---

## ✅ Checklist rápido (10 min)

Use este roteiro sempre antes de encerrar sessão:

1. `cd "/home/deck/Desktop/Github_Projetcs/42/Cube3D/Cube 3D/Parser"`
2. `make -s debug`
3. Validar mapa bom: `./parser_demo ../sample_maps/valid_minimal.cub ; echo "EXIT:$?"`
4. Validar inválidos do Dia 2:
  - `./parser_demo ../sample_maps/invalid_duplicate_element.cub ; echo "EXIT:$?"`
  - `./parser_demo ../sample_maps/invalid_missing_element.cub ; echo "EXIT:$?"`
  - `./parser_demo ../sample_maps/invalid_element_after_map.cub ; echo "EXIT:$?"`
5. Validar Dia 3 (normalização):
  - `./parser_demo ../sample_maps/ragged_valid.cub ; echo "EXIT:$?"`
  - `./parser_demo ../sample_maps/leading_spaces_valid.cub ; echo "EXIT:$?"`
  - `./parser_demo ../sample_maps/mixed_width_valid.cub ; echo "EXIT:$?"`
  - `./parser_demo ../sample_maps/tab_in_map_invalid.cub ; echo "EXIT:$?"`
6. Confirmar resultado esperado:
  - válido: `EXIT:0`
  - inválidos: `EXIT:1` com mensagem clara

Se esse checklist passar, a base do Dia 3 está consistente.

---

## 🧪 Como testar você mesmo (manual)

### Teste 1 — Ordem livre dos elementos

```bash
cat >/tmp/free_order_day2.cub <<'EOF'
F 220,100,0
NO ./textures/north.png
EA ./textures/east.png
C 225,30,0
WE ./textures/west.png
SO ./textures/south.png

111
1N1
111
EOF

./parser_demo /tmp/free_order_day2.cub ; echo "EXIT:$?"
```

Esperado: `EXIT:0`

### Teste 2 — Duplicado

```bash
./parser_demo ../sample_maps/invalid_duplicate_element.cub ; echo "EXIT:$?"
```

Esperado: `EXIT:1` + `duplicate element ...`

### Teste 3 — Faltando elemento

```bash
./parser_demo ../sample_maps/invalid_missing_element.cub ; echo "EXIT:$?"
```

Esperado: `EXIT:1` + `missing required element ...`

### Teste 4 — Elemento depois do mapa

```bash
./parser_demo ../sample_maps/invalid_element_after_map.cub ; echo "EXIT:$?"
```

Esperado: `EXIT:1` + `element after map started ...`

### Teste 5 — Normalização de linhas com tamanhos diferentes

```bash
./parser_demo ../sample_maps/mixed_width_valid.cub ; echo "EXIT:$?"
```

Esperado: `EXIT:0` + logs `[MAP GRID]` e `[MAP i]` preservando layout.

### Teste 6 — Tab no bloco de mapa

```bash
./parser_demo ../sample_maps/tab_in_map_invalid.cub ; echo "EXIT:$?"
```

Esperado: `EXIT:1` + `invalid line ...`

---

## ✅ Resultado esperado dos mapas atuais

| Mapa | Resultado esperado |
|------|--------------------|
| `valid_minimal.cub` | `EXIT:0` |
| `invalid_char.cub` | `EXIT:1` (invalid line) |
| `invalid_open.cub` | `EXIT:0` (ainda sem validação de fechamento) |
| `spawn_colors_demo.cub` | `EXIT:0` |
| `invalid_duplicate_element.cub` | `EXIT:1` |
| `invalid_missing_element.cub` | `EXIT:1` |
| `invalid_element_after_map.cub` | `EXIT:1` |
| `ragged_valid.cub` | `EXIT:0` |
| `leading_spaces_valid.cub` | `EXIT:0` |
| `mixed_width_valid.cub` | `EXIT:0` |
| `tab_in_map_invalid.cub` | `EXIT:1` |

---

## 🧩 Estrutura de código (Parser)

```text
Cube 3D/Parser/
├── includes/
│   ├── parser.h
│   ├── parsing.h
│   ├── parser_config.h
│   ├── elements.h
│   ├── map_grid.h
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
        └── utils/parser_errors.c
```

### Fluxo atual

```text
main_parser.c
  -> load_file_lines(fd)
      -> line_type_name()
      -> parse_element_line()
  -> add_map_line()
      -> validate_required_elements()
  -> extract_map_grid()
  -> free_map_grid()
      -> free_parser_config()
```

---

## 🛠️ Sprint de Implementação (Plano)

### Dia 1  — Base de leitura estável ✅
- **Meta:** fechar leitura de arquivo e classificação inicial de linhas.
- **Entregas:** `load_file_lines`, `is_empty_line`, `is_map_line`, `is_element_line`.
- **Critério de pronto:** imprimir para cada linha o tipo detectado (debug).

### Dia 2 — Parse de elementos ✅
- **Meta:** parsear `NO/SO/WE/EA/F/C` com ordem livre.
- **Entregas:** estrutura de config + detecção de duplicado/faltando.
- **Critério de pronto:** arquivo válido carrega config completa; inválidos dão erro claro.

### Dia 3 — Extração e normalização do mapa ✅
- **Meta:** separar bloco de mapa e montar grade retangular com preenchimento por espaço.
- **Entregas:** `extract_map_grid`, cálculo de largura máxima, cópia preservando layout.
- **Critério de pronto:** mapa “como no arquivo” representado corretamente em memória.

### Dia 4 — Validação estrutural do mapa
- **Meta:** validar charset e spawn.
- **Entregas:** checagem de caracteres válidos + exatamente 1 spawn.
- **Critério de pronto:** `invalid_char` e “2 spawns” falham com mensagem específica.

### Dia 5 — Fechamento do mapa
- **Meta:** validar mapa fechado (sem `0`/spawn tocando vazio/borda).
- **Entregas:** validador de vizinhança (4 direções) e casos de teste de abertura.
- **Critério de pronto:** `invalid_open` falha corretamente; mapa válido passa.

### Dia 6 — Consolidação para entrega
- **Meta:** limpar fluxo final do parser.
- **Entregas:** pipeline único `parse_cub_file`, mensagens de erro padronizadas, revisão de memória.
- **Critério de pronto:** rodar bateria de mapas válidos/inválidos sem crash e com erros consistentes.

---

## 🔎 Observação de debug (Dia 2)

Sim, existe debug útil para Dia 2 e Dia 3:
- `[DEBUG] is_*` para classificação.
- `[LINE N] TYPE | conteúdo` para visão por linha.
- `[MAP GRID] width=... height=...` após normalização.
- `[MAP i] |...|` para inspecionar cada linha da grade final.
- Mensagens claras de erro de elementos.

---

## ✅ Dia 3 Consolidado

**Status:** Pronto para entrega

**O que foi entregue:**
- Módulo `map_grid` com estrutura `t_map_grid` (lines, height, width)
- Acumulação de linhas do mapa durante parsing (preservando layout original)
- Normalização para grade retangular com preenchimento por espaço
- Debug visual: `[MAP GRID] width=... height=...` + `[MAP i] |...|`
- 4 sample maps de validação (ragged, leading_spaces, mixed_width, tab_invalid)

**Validação:**
- Build: `make -s debug` ✅
- Todos os 8 sample maps (Dia 2 + Dia 3) retornam `EXIT:0` ou `EXIT:1` conforme esperado
- Debug output mostra normalização corretamente para cada mapa
- Comentários explicativos adicionados a cada arquivo do módulo map

---

## Próximo foco recomendado

Iniciar **Dia 4** com duas validações centrais:
1. charset final do mapa normalizado (`0`, `1`, `N`, `S`, `E`, `W`, espaço)
2. exatamente 1 spawn no mapa

Depois, adicionar sample maps de erro específico (ex.: `two_spawns_invalid.cub`).
