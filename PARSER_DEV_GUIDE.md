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
  ../sample_maps/invalid_element_after_map.cub; do
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
5. Confirmar resultado esperado:
  - válido: `EXIT:0`
  - inválidos: `EXIT:1` com mensagem clara

Se esse checklist passar, a base do Dia 2 está consistente.

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

---

## 🧩 Estrutura de código (Parser)

```text
Cube 3D/Parser/
├── includes/
│   ├── parser.h
│   ├── parsing.h
│   ├── parser_config.h
│   ├── elements.h
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
        └── utils/parser_errors.c
```

### Fluxo atual

```text
main_parser.c
  -> load_file_lines(fd)
      -> line_type_name()
      -> parse_element_line()
      -> validate_required_elements()
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

### Dia 3 — Extração e normalização do mapa
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

Sim, existe debug útil para o Dia 2:
- `[DEBUG] is_*` para classificação.
- `[LINE N] TYPE | conteúdo` para visão por linha.
- Mensagens claras de erro de elementos.

---

## Próximo foco recomendado

Iniciar **Dia 3** com duas funções centrais:
1. `extract_map_grid`
2. `get_max_map_width`

Depois, adicionar casos de teste com linhas de tamanhos diferentes e espaços internos.
