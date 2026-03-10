# Sprint Parser Cube3D — 6 Dias (10/03 a 15/03)

## Filosofia
- Passo a passo, sem pressa.
- Testar sempre antes de avançar.
- Debug visual quando tiver dúvida.
- Ler código antigo antes de escrever novo.
- Se travar, voltar 1 passo e refazer diferente.

---

# DIA 1 — Classificação de Linhas (10/03)
*"Entender o arquivo antes de parsear."*

## Meta
Conseguir ler o `.cub` inteiro e classificar cada linha corretamente.

## Cronograma Sugerido
- **08:00-09:00** → Estudar o arquivo `.cub`: estrutura geral, regras de layout.
- **09:00-10:30** → Implementar `is_empty_line()` e testar.
- **10:30-12:00** → Implementar `is_map_line()` e testar.
- **13:00-14:30** → Implementar `is_element_line()` e testar.
- **14:30-15:30** → Integrar tudo em um classificador único com debug.
- **15:30-16:00** → Rodar nos 3 mapas de exemplo e conferir.

## Atividades Detalhadas

### 1. Estudo (08:00-09:00)
Abra e leia linha por linha cada mapa de exemplo:
- `sample_maps/valid_minimal.cub`
- `sample_maps/invalid_open.cub`
- `sample_maps/invalid_char.cub`

Responda a si mesmo:
- Qual é o padrão de uma linha vazia?
- Qual é o padrão de uma linha de elemento?
- Qual é o padrão de uma linha de mapa?

### 2. Implement `is_empty_line()` (09:00-09:30)

**Função esperada:**
```c
int is_empty_line(const char *line);
// retorna 1 se a linha é vazia ou só tem espaços/tabs
// retorna 0 caso contrário
```

**Checklist:**
- [ ] Função compila sem warnings.
- [ ] Testa com linha completamente vazia `""`.
- [ ] Testa com linha só espaços `"   "`.
- [ ] Testa com linha só tabs `"\t\t"`.
- [ ] Testa com linha mista espaços+tabs `" \t ".
- [ ] Testa com linha com conteúdo `"NO ./texture.png"`.

**Debug:**
```bash
# Add this to src/parsing/classify_lines.c
#ifdef DEBUG_PARSER
# define DBG(fmt, ...) fprintf(stderr, "[DBG] " fmt "\n", ##__VA_ARGS__)
#else
# define DBG(fmt, ...) (void)0
#endif
```

Depois no seu código teste:
```c
DBG("is_empty_line('%s') = %d", line, is_empty_line(line));
```

### 3. Test `is_empty_line()` (09:30-10:00)

Crie `sample_maps/test_empty_lines.cub`:
```
NO ./texture.png


SO ./texture.png
   
EA ./texture.png
```

Rode o debug e veja:
```bash
cd Parser && make debug && ./parser_demo ../sample_maps/test_empty_lines.cub
```

Saída esperada no stderr:
```
[DBG] is_empty_line('NO ./texture.png') = 0
[DBG] is_empty_line('') = 1
[DBG] is_empty_line('') = 1
[DBG] is_empty_line('SO ./texture.png') = 0
[DBG] is_empty_line('   ') = 1
[DBG] is_empty_line('EA ./texture.png') = 0
```

### 4. Implement `is_map_line()` (10:30-11:30)

**Função esperada:**
```c
int is_map_line(const char *line);
// retorna 1 se a linha parece ser linha de mapa (tem 0, 1, N, S, E, W, ou espaço)
// retorna 0 se tem caractere inválido ou é vazia
```

**Checklist:**
- [ ] Reconhece `"111111"` como map line.
- [ ] Reconhece `"10N001"` como map line.
- [ ] Reconhece `"1 0 1"` como map line (com espaços).
- [ ] REJEITA `"NO ./texture.png"` como map line.
- [ ] REJEITA `"F 100,200,0"` como map line.
- [ ] REJEITA linha vazia como map line.

**Questão importante:** Uma linha só com espaços é map line?
- Resposta: SIM, porque pode ser parte do mapa (vazio/abertura).

### 5. Test `is_map_line()` (11:30-12:00)

Crie `sample_maps/test_map_lines.cub`:
```
111111
10N001
1 0 1
100001
```

Com debug esperado:
```
[DBG] is_map_line('111111') = 1
[DBG] is_map_line('10N001') = 1
[DBG] is_map_line('1 0 1') = 1
[DBG] is_map_line('100001') = 1
```

### 6. Implement `is_element_line()` (13:00-14:00)

**Função esperada:**
```c
int is_element_line(const char *line);
// retorna 1 se a linha começa com NO, SO, WE, EA, F, C
// retorna 0 caso contrário
```

**Checklist:**
- [ ] Reconhece `"NO ./path/texture.png"`.
- [ ] Reconhece `"F 100,200,0"`.
- [ ] Reconhece `"C 50,50,50"`.
- [ ] REJEITA `"111111"` como element.
- [ ] REJEITA linha vazia.
- [ ] Case-sensitive? Decidir: provavelmente não (lowercase é inválido).

### 7. Integrate Classifier (14:30-15:30)

Crie nova função `classify_line`:
```c
typedef enum {
    LINE_EMPTY = 0,
    LINE_ELEMENT = 1,
    LINE_MAP = 2,
    LINE_UNKNOWN = 3
} t_line_type;

t_line_type classify_line(const char *line);
```

Use nas funções anteriores internamente.

**Teste de integração:**
- Leia cada mapa de exemplo.
- Classifique TODAS as linhas.
- Imprima resultado com índice:

```
line[0] (ELEMENT): NO ./textures/north.png
line[1] (ELEMENT): SO ./textures/south.png
line[2] (EMPTY):
line[3] (ELEMENT): F 220,100,0
...
line[8] (MAP): 111111
line[9] (MAP): 100001
...
```

### 8. Final Validation (15:30-16:00)

Rode em todos os 3 mapas + os 2 testes que criou:
```bash
./parser_demo ../sample_maps/valid_minimal.cub
./parser_demo ../sample_maps/invalid_open.cub
./parser_demo ../sample_maps/invalid_char.cub
./parser_demo ../sample_maps/test_empty_lines.cub
./parser_demo ../sample_maps/test_map_lines.cub
```

**Critério de pronto para Dia 1:**
- [ ] 5 testes passam sem crash.
- [ ] Classificação é visualmente correta (debug ativo).
- [ ] Nenhum warning ao compilar.
- [ ] Você entende exatamente o que cada função faz.

---

# DIA 2 — Parse de Elementos (11/03)
*"Extrair os metadados do arquivo."*

## Meta
Ler linhas de `NO/SO/WE/EA/F/C` e montar estrutura de config válida.

## Cronograma Sugerido
- **08:00-09:00** → Criar struct `t_config` e pensar em design.
- **09:00-10:30** → Implementar parser de `NO/SO/WE/EA`.
- **10:30-12:00** → Implementar parser de `F` e `C` (RGB).
- **13:00-14:00** → Validar duplicados e presença de todos.
- **14:00-15:30** → Integrar com leitor de linhas + debug.
- **15:30-16:00** → Testar em mapas variados.

## Atividades Detalhadas

### 1. Design da Struct (08:00-09:00)

**Estude:**
- O que precisa armazenar? (4 texturas, 2 cores, mais alguma coisa?)
- Como representar um RGB? (ex: `typedef struct { int r, g, b; } t_rgb;`)

**Proposta de struct:**
```c
typedef struct s_config {
    char    *path_no;
    char    *path_so;
    char    *path_we;
    char    *path_ea;
    t_rgb   floor_color;
    t_rgb   ceiling_color;
    int     flags;  // bitmask para saber qual foi parsado
}t_config;
```

**Discuta consigo:**
- Vale usar bitmask para flags ou array de ints?
- Como inicializar a struct (valores default)?

### 2. Parser de Texturas (09:00-10:30)

**Função:**
```c
int parse_texture_line(const char *line, t_config *cfg);
// retorna 0 se falha, 1 se sucesso
// detecta NO/SO/WE/EA, extrai path
// marca no cfg->flags que foi parsado
```

**Checklist:**
- [ ] Extrai `NO` + path corretamente.
- [ ] Extrai `SO` + path corretamente.
- [ ] Extrai `WE` + path corretamente.
- [ ] Extrai `EA` + path corretamente.
- [ ] Detecta duplicado `NO` (falha com erro claro).
- [ ] Permite espaços extras: `NO    ./path.png`.
- [ ] Alocar memória para path com `strdup`.
- [ ] Free de paths antigos se duplicado.

**Debug esperado:**
```
[DBG] parse_texture_line('NO ./textures/north.png') -> flags=0x01, path="./textures/north.png"
[DBG] parse_texture_line('SO ./textures/south.png') -> flags=0x03, path="./textures/south.png"
```

### 3. Parser de Cores (10:30-12:00)

**Função:**
```c
int parse_color_line(const char *line, t_config *cfg);
// retorna 0 se falha, 1 se sucesso
// detecta F ou C, extrai r,g,b (0-255)
// marca no cfg->flags que foi parsado
```

**Checklist:**
- [ ] Parse `F 220,100,0` → `floor_color = {220, 100, 0}`.
- [ ] Parse `C 225,30,0` → `ceiling_color = {225, 30, 0}`.
- [ ] Permite espaços: `F  220 , 100 , 0`.
- [ ] REJEITA RGB fora da faixa: `F 999,100,0` (falha).
- [ ] REJEITA RGB negativo: `F -1,100,0` (falha).
- [ ] REJEITA RGB com chars estranhos: `F 100,abc,0` (falha).
- [ ] Detecta duplicado `F` (falha com erro).

**Debug esperado:**
```
[DBG] parse_color_line('F 220,100,0') -> floor_color={220,100,0}, flags=0x1C
[DBG] parse_color_line('C 225,30,0') -> ceiling_color={225,30,0}, flags=0x1E
```

**Teste manual de parse de RGB:**
Crie função auxiliar de teste:
```c
void test_parse_rgb(const char *str) {
    int r, g, b;
    if (sscanf(str, "%d,%d,%d", &r, &g, &b) != 3)
        printf("FAIL: %s\n", str);
    else if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        printf("OUT_OF_RANGE: %s\n", str);
    else
        printf("OK: %s -> (%d,%d,%d)\n", str, r, g, b);
}
```

### 4. Validação Global (13:00-14:00)

**Função:**
```c
int validate_config(const t_config *cfg);
// retorna 1 se tudo presente, 0 se falta algo
```

**Checklist:**
- [ ] Verifica se os 4 caminhos de textura estão zerados (não parsados).
- [ ] Verifica se F foi parsado.
- [ ] Verifica se C foi parsado.
- [ ] Mensagem de erro específica para cada falta.
- [ ] Não precisa validar se paths existem (ainda).

**Mensagens de erro propostas:**
```
Error: texture NO not specified
Error: texture SO not specified
Error: floor color (F) not specified
Error: ceiling color (C) not specified
```

### 5. Integração com Loop (14:00-15:30)

**Pipeline:**
```
load_file_lines() 
  → classify each line
    → if ELEMENT, parse_texture_line or parse_color_line
    → accumulate config
    → keep track of line number para mensagens de erro
  → no final, validate_config
```

Teste com `valid_minimal.cub`:
```
[DBG] Line 0: NO ./textures/north.png (ELEMENT) ✓
[DBG] Line 1: SO ./textures/south.png (ELEMENT) ✓
[DBG] Line 2: WE ./textures/west.png (ELEMENT) ✓
[DBG] Line 3: EA ./textures/east.png (ELEMENT) ✓
[DBG] Line 5: F 220,100,0 (ELEMENT) ✓
[DBG] Line 6: C 225,30,0 (ELEMENT) ✓
[DBG] Config validation: PASS
```

### 6. Final Validation (15:30-16:00)

**Testes:**
1. `valid_minimal.cub` → deve passar.
2. Crie `sample_maps/missing_no.cub` (sem `NO` → deve falhar).
3. Crie `sample_maps/bad_rgb.cub` (`F 999,0,0` → deve falhar).
4. Crie `sample_maps/dup_f.cub` (dois `F` → deve falhar).
5. Crie `sample_maps/wrong_order.cub` (mesmo com ordem diferente → deve passar).

**Critério de pronto para Dia 2:**
- [ ] 5 testes: 1 passa, 4 falham com mensagem clara.
- [ ] Config completa armazenada em struct.
- [ ] Nenhum memory leak (valgrind se conseguir).
- [ ] Debug liga/desliga com `make debug`.

---

# DIA 3 — Extração e Normalização do Mapa (12/03)
*"Do arquivo para uma grade em memória."*

## Meta
Ler o bloco de mapa e montar matriz retangular preenchendo com espaço.

## Cronograma Sugerido
- **08:00-09:00** → Estudar layout de mapa (linhas irregulares, espaços, padding).
- **09:00-10:30** → Implementar `find_map_start()` e `find_map_end()`.
- **10:30-12:00** → Implementar `normalize_map()` (preenchimento com espaço).
- **13:00-14:00** → Testar normalização visual (abrir no visual_demo).
- **14:00-15:00** → Debug de edge cases (mapa vazio, 1 linha, etc).
- **15:00-16:00** → Integração com parser completo.

## Atividades Detalhadas

### 1. Estudo de Layout (08:00-09:00)

**Abra `valid_minimal.cub` e observe:**
- Linha 8: `111111` (6 chars)
- Linha 9: `100001` (6 chars)
- Linha 10: `10N001` (6 chars)
- Linha 11: `100001` (6 chars)
- Linha 12: `111111` (6 chars)

→ Mapa retangular já.

**Agora crie `sample_maps/irregular_map.cub`:**
```
NO ./textures/north.png
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png
F 220,100,0
C 225,30,0

1111111
10N0001
10000
100001
1111111
```

Observe:
- Linha "10000" tem só 5 chars (não 7).
- Precisa ser preenchida com espaços na direita.

### 2. Implementar `find_map_start()` (09:00-09:45)

**Função:**
```c
int find_map_start(const t_file_lines *file_lines);
// retorna índice da primeira linha que é map_line
// retorna -1 se não achar (erro)
```

**Checklist:**
- [ ] Encontra primeira map_line em `valid_minimal.cub` (deve ser linha 8).
- [ ] Encontra primeira map_line em `irregular_map.cub`.
- [ ] Retorna -1 se arquivo tem SÓ config, nenhum mapa.

### 3. Implementar `find_map_end()` (09:45-10:30)

**Função:**
```c
int find_map_end(const t_file_lines *file_lines, int start);
// retorna índice da primeira linha NÃO-map_line a partir de start
// retorna file_lines->count se mapa vai até fim do arquivo
```

**Checklist:**
- [ ] Em `valid_minimal.cub`: start=8, retorna 13 (count).
- [ ] Em `irregular_map.cub`: start=8, retorna 13 (count).
- [ ] Crie `sample_maps/map_with_trailing.cub` (mapa, depois linhas vazias, depois lixo):
  ```
  ...config...
  
  111111
  100001
  111111
  
  
  garbage text here
  ```
  → Deve parar na primeira linha vazia ou garbage.

### 4. Implementar `normalize_map()` (10:30-12:00)

**Função:**
```c
t_map_grid *normalize_map(const t_file_lines *file_lines, int start, int end);
// aloca grid, descobre largura máxima
// preenche linhas com espaço na direita se irregular
// retorna ponteiro para t_map_grid ou NULL se erro
```

**Checklist:**
- [ ] Descobre largura = max de todas as linhas.
- [ ] Aloca `height` linhas (end - start).
- [ ] Aloca cada linha com `width + 1` (+ null terminator).
- [ ] Preenche linhas curtas com espaço.
- [ ] Testa em `valid_minimal.cub` (6x5 retangular).
- [ ] Testa em `irregular_map.cub` (7x5, precisa normalizar).
- [ ] Debug: imprime grid normalizada.

**Debug proposto:**
```c
void debug_print_grid(const t_map_grid *grid) {
    printf("[DEBUG] Map grid: %zux%zu\n", grid->width, grid->height);
    for (size_t y = 0; y < grid->height; y++) {
        printf("  row[%zu] = [%s]\n", y, grid->rows[y]);
    }
}
```

### 5. Testar Visualmente (13:00-14:00)

**Compile visual_demo (já deve estar pronto):**
```bash
cd Parser && make visual
```

**Abra em visual:**
```bash
./visual_demo ../sample_maps/valid_minimal.cub
./visual_demo ../sample_maps/irregular_map.cub
```

Você deve VER:
- Primeiro: grid 6x5, fechado.
- Segundo: grid 7x5, com normalizando visível (espaços extras).

### 6. Debug de Edge Cases (14:00-15:00)

**Crie testes:**
1. `sample_maps/empty_map.cub` (só config, nenhuma linha de mapa):
   → find_map_start retorna -1 → erro.

2. `sample_maps/one_line_map.cub` (só 1 linha de mapa):
   → deve funcionar (grid 1x1).

3. `sample_maps/one_cell_map.cub` (grid 1x1):
   ```
   ...config...
   
   1
   ```

4. `sample_maps/all_spaces_map.cub` (grid só com espaços):
   ```
   ...config...
   
   
   
   
   ```
   → Deve alocar e normalizar (grid com todas vazias).

### 7. Integração Final (15:00-16:00)

**Pipeline completo:**
```
load_file_lines()
  → parse_config() [de Dia 2]
  → find_map_start() [novo, hoje]
  → find_map_end() [novo, hoje]
  → normalize_map() [novo, hoje]
  → retorna struct com config + grid
```

**Teste em todos os 4 edge cases + 2 mapas bem formados = 6 testes.**

**Critério de pronto para Dia 3:**
- [ ] 6 testes compila sem crash.
- [ ] visual_demo mostra grids corretamente (espaços visíveis).
- [ ] Edge cases tratados (strings vazias, 1 célula, etc).
- [ ] Nenhum memory leak.

---

# DIA 4 — Validação de Caracteres e Spawn (13/03)
*"O mapa só pode ter 0, 1, N, S, E, W, e espaço."*

## Meta
Garantir que mapa contém apenas caracteres válidos e exatamente 1 spawn.

## Cronograma Sugerido
- **08:00-09:00** → Entender regras de caracteres válidos.
- **09:00-10:30** → Implementar `validate_map_charset()`.
- **10:30-12:00** → Implementar `find_and_validate_spawn()`.
- **13:00-14:00** → Testar com mapas variados.
- **14:00-15:30** → Integração e debug.
- **15:30-16:00** → Validação final.

## Atividades Detalhadas

### 1. Estudo (08:00-09:00)

**Caracteres válidos no mapa:**
- `0` = espaço vazio, jogável.
- `1` = parede.
- `N/S/E/W` = spawn (player start + direção inicial).
- espaço ` ` = parte do mapa (vazio fora da área jogável, ou borda).

**O que é INVÁLIDO:**
- Qualquer outra letra (`X`, `P`, `M`, etc).
- Números fora de 0-1 (`2`, `3`, `-1`, etc).
- Caracteres especiais (`@`, `#`, `$`, etc).

### 2. Validar Charset (09:00-10:30)

**Função:**
```c
int validate_map_charset(const t_map_grid *grid);
// retorna 1 se só tem 0, 1, N, S, E, W, espaço
// retorna 0 e imprime erro se char inválido
// erro: linha Y, posição X, char inválido
```

**Checklist:**
- [ ] Aceita `1` (parede).
- [ ] Aceita `0` (chão).
- [ ] Aceita `N/S/E/W` (spawn).
- [ ] Aceita espaço ` `.
- [ ] REJEITA `2` com mensagem clara.
- [ ] REJEITA `X` com mensagem clara.
- [ ] REJEITA letra minúscula (`n`, `s`, etc).
- [ ] Mensagem de erro: "Map error at (row Y, col X): invalid char 'X'".

**Teste em `invalid_char.cub` (tem `X`):**
→ Deve falhar com erro claro.

### 3. Encontrar e Validar Spawn (10:30-12:00)

**Função:**
```c
typedef struct s_spawn {
    size_t  x;
    size_t  y;
    char    dir;  // N, S, E, W
} t_spawn;

int find_and_validate_spawn(const t_map_grid *grid, t_spawn *out_spawn);
// retorna 1 e preenche out_spawn se exatamente 1 spawn
// retorna 0 e imprime erro se 0 ou múltiplos spawns
```

**Checklist:**
- [ ] Encontra `N` em (2, 1) em `valid_minimal.cub`.
- [ ] Encontra `N`, `S`, `E`, `W` em (1,1), (2,3), (3,5), (3,1) em `spawn_colors_demo.cub`.
- [ ] REJEITA se tem 0 spawns com erro "No spawn found".
- [ ] REJEITA se tem 2+ spawns com erro "Multiple spawns found at (X,Y) and (X2,Y2)".

**Debug esperado:**
```
[DBG] Found spawn 'N' at (2, 1)
[DBG] Validating spawn uniqueness... OK
```

**Crie testes:**
1. `sample_maps/no_spawn.cub` (só 0s e 1s):
   → Falha com "No spawn found".

2. `sample_maps/two_spawns.cub` (tem N em (1,1) e S em (3,3)):
   → Falha com "Multiple spawns found".

### 4. Teste Integrado (13:00-14:00)

**Teste em ordem:**
```
valid_minimal.cub       → passa
invalid_char.cub        → falha (char inválido)
no_spawn.cub            → falha (sem spawn)
two_spawns.cub          → falha (múltiplos)
spawn_colors_demo.cub   → falha aqui sim? (tem 4 spawns)
                           → devemos rejEITAR
```

**Output esperado para cada erro:**
```
$ ./parser_demo ../sample_maps/invalid_char.cub
Error: Map error at (2, 1): invalid char 'X'

$ ./parser_demo ../sample_maps/no_spawn.cub
Error: No spawn found in map

$ ./parser_demo ../sample_maps/two_spawns.cub
Error: Multiple spawns found at (1,1) and (3,3)
```

### 5. Integração (14:00-15:30)

**Pipeline:**
```
normalize_map()
  → validate_map_charset()
  → find_and_validate_spawn()
  → acumular spawn em struct separada
```

**Retornar error code claro:**
```c
typedef enum {
    PARSE_OK = 0,
    PARSE_ERR_CHARSET = 1,
    PARSE_ERR_NO_SPAWN = 2,
    PARSE_ERR_MULTI_SPAWN = 3,
    // ... outros
} t_parse_error;
```

### 6. Validação Final (15:30-16:00)

**Critério de pronto para Dia 4:**
- [ ] 5 testes (1 passa, 4 falham com erro específico).
- [ ] Cada erro tem mensagem clara (linha, coluna, tipo).
- [ ] Spawn é armazenado corretamente.
- [ ] Nenhum crash.

---

# DIA 5 — Fechamento do Mapa (14/03)
*"Não pode ter chão (0) tocando vazio ou borda."*

## Meta
Validar que mapa está geometricamente fechado (não há buracos).

## Cronograma Sugerido
- **08:00-09:00** → Estudar "fechamento" (conceito geométrico).
- **09:00-10:30** → Implementar `is_cell_open()`.
- **10:30-12:00** → Implementar `validate_map_closed()`.
- **13:00-14:00** → Teste em mapas abertos via visual_demo.
- **14:00-15:30** → Debug e edge cases.
- **15:30-16:00** → Integração final.

## Atividades Detalhadas

### 1. Conceito de Fechamento (08:00-09:00)

**Regra crítica:**
Todo `0` (chão jogável) e spawn (`N/S/E/W`) deve estar cercado por `1` (parede).
Se um `0` ou spawn tocar um espaço ` ` ou a borda da matriz, o mapa está aberto.

**Exemplo:**
```
11111
1000N
11111
```
← Aqui o `N` toca a borda direita (coluna 4, mas width=5 → índice máximo é 4).
→ Mapa ABERTO.

**Exemplo correto:**
```
111111
1000N1
111111
```
← Aqui tudo está cercado.
→ Mapa FECHADO.

### 2. Implementar `is_cell_open()` (09:00-10:30)

**Função:**
```c
int is_cell_open(const t_map_grid *grid, size_t x, size_t y);
// retorna 1 se (x,y) é 0 ou spawn E toca vazio/borda
// retorna 0 caso contrário
```

**Lógica:**
```
Se grid[y][x] é '0' ou 'N/S/E/W':
    Checar os 4 vizinhos (cima, baixo, esquerda, direita):
    - Se vizinho está fora da matriz → OPEN
    - Se vizinho é ' ' (espaço) → OPEN
    - Se todos os vizinhos são '1' ou outro 0 → OK
```

**Pseudo-code:**
```c
if (grid[y][x] != '0' && !is_spawn(grid[y][x]))
    return 0;  // não é célula de interesse

// check bounds
if (x == 0 || x + 1 == grid->width || y == 0 || y + 1 == grid->height)
    return 1;  // toca borda

// check vizinhos
char left = grid[y][x-1];
char right = grid[y][x+1];
char up = grid[y-1][x];
char down = grid[y+1][x];

if (left == ' ' || right == ' ' || up == ' ' || down == ' ')
    return 1;  // toca vazio

return 0;  // fechado
```

**Checklist:**
- [ ] Célula `0` na borda retorna 1 (open).
- [ ] Célula `0` cercada por `1` retorna 0 (closed).
- [ ] Célula `0` vizinha de ` ` retorna 1 (open).
- [ ] Spawn `N` na borda retorna 1 (open).

### 3. Testar Visualmente com `invalid_open.cub` (antes do código de fechamento)

```bash
# Mapa inválido já tem uma célula aberta
# Devemos visualizar onde está
./visual_demo ../sample_maps/invalid_open.cub
```

Você verá amarelo marcando as células abertas (implementado em Dia 1).

### 4. Implementar `validate_map_closed()` (10:30-12:00)

**Função:**
```c
int validate_map_closed(const t_map_grid *grid);
// varre todas as células
// se alguma 0 ou spawn está aberta, falha
// retorna 1 se fechado, 0 se aberto
```

**Checklist:**
- [ ] `valid_minimal.cub` retorna 1 (fechado).
- [ ] `invalid_open.cub` retorna 0 (aberto), imprime erro.
- [ ] Erro menciona coordenada da célula aberta: "Map error: floor/spawn cell at (2,3) is not enclosed".

### 5. Testar em Mapas Variados (13:00-14:00)

**Crie testes:**
1. `sample_maps/open_top.cub`:
   ```
   111111
   100001
   100001
   ```
   → Célula em (1,0) toca borda de cima.

2. `sample_maps/open_left.cub`:
   ```
   111111
   0N0001
   111111
   ```
   → Célula em (0,1) toca borda esquerda.

3. `sample_maps/open_void.cub`:
   ```
   111111
   1 0001
   111111
   ```
   → Célula em (1,1) é `0`, vizinha de ` ` à esquerda.

4. `sample_maps/closed_properly.cub`:
   ```
   1111111
   1N00001
   1000001
   1111111
   ```
   → Deve passar.

**Teste todos:**
```bash
./parser_demo ../sample_maps/open_top.cub
./parser_demo ../sample_maps/open_left.cub
./parser_demo ../sample_maps/open_void.cub
./parser_demo ../sample_maps/closed_properly.cub
```

### 6. Visualizar Diferenças (14:00-15:00)

**Abra os abertos no visual_demo:**
```bash
./visual_demo ../sample_maps/open_top.cub
./visual_demo ../sample_maps/open_void.cub
./visual_demo ../sample_maps/closed_properly.cub
```

Você verá:
- Abertos: células amarelas marcando o problema.
- Fechado: sem amarelo.

### 7. Integração (15:00-15:30)

**Pipeline completo:**
```
validate_map_charset()
  → find_and_validate_spawn()
  → validate_map_closed()   ← novo, hoje
```

### 8. Validação Final (15:30-16:00)

**Critério de pronto para Dia 5:**
- [ ] 4 testes (1 passa, 3 falham com erro específico).
- [ ] Mensagens de erro mencionam coordenada exata.
- [ ] Visual_demo mostra amarelo para abertos, nada para fechados.
- [ ] Responde pergunta: "spawn toca borda?" → passa se borda = 1 (parede).

---

# DIA 6 — Consolidação e Entrega (15/03)
*"Tudo junto, testado, pronto."*

## Meta
Fechar o pipeline do parser sem crashes, com erros consistentes, pronto para entrega.

## Cronograma Sugerido
- **08:00-09:00** → Revisar todo o código escrito (Dia 1-5).
- **09:00-10:30** → Limpar redundâncias, refatorar se necessário.
- **10:30-12:00** → Bateria de TODOS os testes (32 testes total?).
- **13:00-14:00** → Memory leaks check (valgrind).
- **14:00-15:00** → Documentação e README atualizado.
- **15:00-16:00** → Deploy final, fclean, commit.

## Atividades Detalhadas

### 1. Code Review (08:00-09:00)

**Leia novamente, linha por linha:**
- `parsing.h`, `utils.h` → lógica clara?
- `src/parsing/*.c` → sem código duplicado?
- `src/utils/*.c` → apenas helpers simples?

**Checklist:**
- [ ] Nenhuma variável global.
- [ ] Todas as funções bem documentadas (comentarios em cima).
- [ ] Nomes varíaveis descritivos (não `x`, `temp`, etc).

### 2. Refatoring (09:00-10:30)

**Se encontrar:**
- Código duplicado → extrair para função.
- Função muito longa (>50 linhas) → quebrar em sub-funções.
- Variável global → passar como parâmetro.

**Deploy limpo:**
```
src/parsing/
├── load_file.c
├── classify_lines.c
├── parse_elements.c
├── extract_map.c
├── validate_charset.c
├── validate_spawn.c
└── validate_closed.c

src/utils/
├── file_lines_utils.c
├── memory_utils.c (free functions)
└── debug_utils.c (optional)
```

### 3. Bateria de Testes (10:30-12:00)

**Organize todos os `.cub` criados:**
- `valid_minimal.cub` → PASS
- `spawn_colors_demo.cub` → FAIL (4 spawns)
- `invalid_open.cub` → FAIL (open)
- `invalid_char.cub` → FAIL (char inválido)
- Mais 28 casos edge...

**Script de teste (em shell ou Python):**
```bash
#!/bin/bash
PASS=0
FAIL=0

test_map() {
    local file=$1
    local expected=$2  # "pass" ou "fail"
    
    ./parser_demo "$file" 2>&1 | grep -q "Error"
    local has_error=$?
    
    if [ "$expected" = "pass" ] && [ $has_error -eq 1 ]; then
        echo "✓ $file"
        ((PASS++))
    elif [ "$expected" = "fail" ] && [ $has_error -eq 0 ]; then
        echo "✓ $file (failed as expected)"
        ((PASS++))
    else
        echo "✗ $file (unexpected result)"
        ((FAIL++))
    fi
}

# rodar testes
test_map "../sample_maps/valid_minimal.cub" "pass"
test_map "../sample_maps/invalid_open.cub" "fail"
# ... 30+ testes

echo "Results: $PASS passed, $FAIL failed"
```

### 4. Memory Leaks (13:00-14:00)

**Se valgrind disponível:**
```bash
valgrind --leak-check=full ./parser_demo ../sample_maps/valid_minimal.cub
```

**Procure por:**
- "definitely lost" → fix imediato.
- "indirectly lost" → verificar.
- "possibly lost" → OK em geral (pode ser da libc).

**Se não tiver valgrind:**
- Revisar código com olho: `malloc` → `free` em pares.
- Verificar `strdup` → `free` em pares.

### 5. Documentação (14:00-15:00)

**Atualizar `README.md`:**

```markdown
# Cube3D Parser

## Estrutura

### Dias de Desenvolvimento

- **Dia 1**: Classificação de linhas
  - `is_empty_line()`, `is_map_line()`, `is_element_line()`
  
- **Dia 2**: Parse de elementos
  - `parse_texture_line()`, `parse_color_line()`, `validate_config()`
  
- **Dia 3**: Extração e normalização
  - `normalize_map()`, preenchimento com espaço
  
- **Dia 4**: Validação de charset e spawn
  - `validate_map_charset()`, `find_and_validate_spawn()`
  
- **Dia 5**: Validação de fechamento
  - `validate_map_closed()`, detecção de buracos
  
- **Dia 6**: Consolidação
  - Pipeline completo, testes, entrega

## Como Compilar

```bash
cd Parser
make        # compilação normal
make debug  # com output debug
make visual # com viewer MLX
```

## Como Testar

```bash
./parser_demo ../sample_maps/valid_minimal.cub
./parser_demo ../sample_maps/invalid_open.cub
...
```

## Próximos Passos

Depois do parser:
- Inicializar jogador (position + angle de spawn).
- Implementar raycasting (loop principal).
- Render com texturas e MLX.
```

### 6. Deploy Final (15:00-16:00)

**Checklist final:**
- [ ] `make fclean` remove todos artefatos.
- [ ] `make` compila sem warnings.
- [ ] `make debug` compila e imprime corretamente.
- [ ] `make visual` abre visual_demo.
- [ ] 32+ testes passam ou falham conforme esperado.
- [ ] Nenhum memory leak detectado.
- [ ] README atualizado.
- [ ] Código commitado no git.

**Comandos finais:**
```bash
cd Parser
make fclean
make
# testes...
make debug
# mais testes...
make clean
git add -A
git commit -m "Parser: complete 6-day sprint, all validations working"
```

**Critério de Entrega:**
- [ ] Parser compila sem warning.
- [ ] 32+ testes: os que devem passar passam, os que devem falhar falham.
- [ ] Cada erro tem mensagem clara (linha, tipo de erro).
- [ ] Nenhum crash.
- [ ] Nenhum memory leak.
- [ ] Você consegue EXPLICAR cada função.

---

## Notas Gerais

**Se travar em algum dia:**
1. Releia o exercício do dia anterior.
2. Rode com `make debug` e estude a saída.
3. Abra `visual_demo` para visualizar.
4. Se ainda assim não entender, volte um passo e refaça diferente.

**Se ficar para trás:**
- Não se apresse.
- Dias 1-3 são a base; se não passar neles, os dias 4-6 não funcionam.
- Melhor terminar em 7-8 dias com tudo funcionando do que 6 dias com bugs.

**Celebre vitórias pequenas!**
- Depois de Dia 1: você entende o arquivo.
- Depois de Dia 2: você extrai metadados.
- Depois de Dia 3: você tem mapa em memória.
- Depois de Dia 4: você garante caracteres válidos.
- Depois de Dia 5: você detecta buracos.
- Depois de Dia 6: **você TEM um parser!** 🎉

Boa sorte, e sucesso! 💪
