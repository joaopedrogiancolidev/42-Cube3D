# Resumo Executivo: Semana 1 Cube3D (10/03/2026)

## O Que Fizemos

### Prototipagem (Parser/Protótipo)
- Leitura simples de linhas do arquivo `.cub` com `getline`.
- Classificação de linhas: **vazia**, **elemento**, **mapa**.
- Parser de elementos (`NO/SO/WE/EA/F/C`) com validação de RGB.
- Extração e normalização do mapa em grade retangular.
- Visualização em 2D com MLX:
  - **Azul escuro** = parede `1`
  - **Cinza claro** = chão `0`
  - **Vermelho** = spawn `N`
  - **Azul** = spawn `S`
  - **Verde** = spawn `E`
  - **Roxo** = spawn `W`
  - **Amarelo** = células abertas/suspeitas
  - **Preto** = vazio/espaço

### Estrutura de Projeto
```
Cube 3D/
├── Parser/
│   ├── src/
│   │   ├── main.c / visual_main.c
│   │   ├── parsing/
│   │   │   └── load_file.c
│   │   ├── utils/
│   │   │   └── file_lines_utils.c
│   │   └── visual/
│   │       ├── extract_map.c
│   │       └── render_map.c
│   ├── includes/
│   │   ├── parser.h (agregador)
│   │   ├── parsing.h
│   │   ├── utils.h
│   │   └── visual.h
│   └── Makefile (com targets debug e visual)
├── sample_maps/
│   ├── valid_minimal.cub
│   ├── invalid_open.cub
│   ├── invalid_char.cub
│   └── spawn_colors_demo.cub
├── SPRINT_6_DAYS_PARSER.md (guia detalhado)
└── README.md
```

### Ferramentas Criadas
- **parser_demo**: leitor básico com debug de linhas.
- **visual_demo**: visualizador de mapa em cores sem texturas.
- Modo `make debug` para ativar prints detalhados.
- Legenda impressa no terminal ao abrir visual_demo.

## Próximos Passos (Sprint de 6 Dias)

**Veja:** `SPRINT_6_DAYS_PARSER.md` para cronograma hora a hora.

**Resumo dos 6 dias:**
1. **Dia 1** → Classificar linhas (vazia/elemento/mapa).
2. **Dia 2** → Parsear elementos (`NO/SO/WE/EA/F/C`).
3. **Dia 3** → Normalizar mapa em memória.
4. **Dia 4** → Validar charset e spawn único.
5. **Dia 5** → Validar fechamento (sem buracos).
6. **Dia 6** → Consolidar, testar tudo, entrega.

## Como Rodar Agora

```bash
# Ir para o protótipo
cd 'Cube 3D/Parser'

# Compilar
make
make debug    # com prints
make visual   # com visualizador

# Rodar reader básico
./parser_demo ../sample_maps/valid_minimal.cub

# Visualizar mapa
./visual_demo ../sample_maps/valid_minimal.cub
./visual_demo ../sample_maps/invalid_open.cub
./visual_demo ../sample_maps/spawn_colors_demo.cub

# Limpar
make fclean
```

## Dicas Importantes

1. **Estude o arquivo `.cub` antes de codar** → entenda a estrutura.
2. **Teste incremental** → compile e rode a cada pequena mudança.
3. **Use debug com `make debug`** → veja o fluxo interno.
4. **Visualize com MLX** → às vezes é mais fácil ver do que ler logs.
5. **Se travar, volte um passo** → não force, refaça de outro ângulo.

## Meta Final

No final dos 6 dias, você terá:
- ✅ Parser que lê e valida `.cub`.
- ✅ Detecção de erros clara (mensagem + coordenada).
- ✅ Mapa em memória pronto para raycasting.
- ✅ Spawn identificado (posição + ângulo).
- ✅ Zero crashes, zero memory leaks.

Depois disso:
- Integrar raycasting (tutorial do Lode).
- Render com MLX + texturas.
- Bônus: minimap, animações, etc.

**Boa sorte! 💪**
